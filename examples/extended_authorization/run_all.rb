#!/usr/bin/env ruby


authd_pid =  fork do
  exec "./pure-authd -s /tmp/ftpd.sock -r #{Dir.pwd}/auth_script"
end

pure_ftpd =  fork do
  exec "./pure-ftpd -lextauth:/tmp/ftpd.sock"
end


trap("INT") do
  Process.kill("TERM", authd_pid) rescue nil
  Process.kill("TERM", authd_pid) rescue nil
end

Process.wait rescue nil
Process.wait rescue nil
