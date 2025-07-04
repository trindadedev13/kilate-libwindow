require "fileutils"
require "timeout"

def run(cmd)
  puts cmd
  s = system(cmd)
  abort("Failed #{cmd} : #{s}") unless s
end

def build_libkw()

  lib_files = [
    "src/Main.cpp",
    "src/KwWindow.cpp",
    "src/Register.cpp",
    "src/Windows/KwWindow.cpp",
    "src/Unix/KwWindow.cpp",
  ]

  kltpp_files = [
    "Kilatepp/src/Native.cpp"
  ]

  files = []
  files.push(lib_files)
  files.push(kltpp_files)

  args = [
    "-shared",
    "-fpic",
    "-o libkwindow.so",
    "-Iinclude/",
    "-IKilatepp/include/",
    "-lX11",
    "#{files.join(' ')}"
  ].join(" ")

  run("g++ #{args}")

  # Windows: gcc -shared -fpic -o libkwindow.so main.c impl.c -std=c23 -mwindows

  home = ENV["HOME"]
  ENV["DISPLAY"] = ":0"
  termux = true

  FileUtils.mkdir_p("#{home}/temp/libkwindow/")
  FileUtils.mv("libkwindow.so", "#{home}/temp/libkwindow/libkwindow.so")

  FileUtils.cp("main.klt", "#{home}/temp/libkwindow/main.klt")

  def cleanup_x11(pid)
    puts "Shutting down X11 (PID #{pid})..."
    begin
      Process.kill("TERM", pid)
      sleep 1
      Process.wait(pid)
    rescue Errno::ESRCH
      puts "Process already died (PID #{pid})"
    rescue Errno::ECHILD
      puts "Process has already been reused"
    rescue e
      puts "Failed to kill #{pid}: #{e}"
    end
    exit
  end

  Dir.chdir("#{home}/temp/libkwindow/") do
    if termux
      x11_pid = spawn({"DISPLAY" => ENV["DISPLAY"]}, "termux-x11 :0")

      Signal.trap("INT") do
        cleanup_x11(x11_pid)
      end

      begin
        Timeout.timeout(10) do
          until File.exist?("#{ENV["PREFIX"]}/tmp/.X11-unix/X0")
            sleep 0.5
          end
        end
        puts "X11 is ready"
      rescue Timeout::Error
        cleanup_x11(x11_pid)
        abort "X11 did not initialize: socket timeout"
      end

      run("kilate run main.klt")

      cleanup_x11(x11_pid)
    else
      run("kilate run main.klt")
    end
  end
end

build_libkw()