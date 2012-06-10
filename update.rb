# This script downloads all (new) releases of pureftp, and updates this git repository.

require "net/ftp"
require "uri"

module PureFTPUpdater
  extend self

  SKIP_FILES = ["update.rb", "README.md"] # These files are not part of the pure-ftpd repository

  URLS = [
    "ftp://download.pureftpd.org/pub/pure-ftpd/releases/obsolete/pure-ftpd-:version.tar.bz2",
    "ftp://download.pureftpd.org/pub/pure-ftpd/releases/pure-ftpd-:version.tar.bz2"
  ]


  # Check which releases are available, and import the history of the ones we don't know yet.
  def update!
    releases = find_releases URLS

    releases.sort_by! { |release, path| release }

    releases.each do |release, uri|
      print "- #{release} "

      if already_imported?(release)
        puts "Already imported"
      else
        puts "Not yet imported."
        import release, uri
      end
    end
  end

private
  
  # Find all available releases
  def find_releases url
    if url.kind_of? Array
      return url.map { |u| find_releases u }.flatten(1)
    end

    Net::FTP.open(hostname_for(url)) do |ftp|
      ftp.login
      ftp.chdir dir_for url
      files = ftp.nlst pattern_for url

      files.map do |file|
        uri = URI("ftp://#{hostname_for(url)}/#{File.join(dir_for(url), file)}")
        [extract_version_from(file, url), uri]
      end
    end
  end

  # Checks if we've already downloaded a certain release
  def already_imported? release
    releases_imported.member?("v#{release}")
  end

  def import release, ftp_uri
    puts "  Import #{ftp_uri.path}"
    clean_dir!
    download ftp_uri
    commit! "  Imported #{ftp_uri.path}"
    tag! release
  end

  # Helper functions
  def clean_dir!
    attempt = 0
    while (files = Dir["**/*"]).length > SKIP_FILES.length
      attempt += 1
      raise "Could not clean dir" if attempt > 100
      files.each do |file|
        if SKIP_FILES.member?(file)
          next
        else
          `rm -rf #{file}`
        end
      end
    end
  end

  # Download, extract and clean up
  def download uri
    print "  Downloading... "
    Net::FTP.open(uri.hostname) do |ftp|
      ftp.login
      ftp.getbinaryfile(uri.path, "pureftpd.tar.bz2")
    end
    print " extracting ..."
    `tar -xf pureftpd.tar.bz2 `
    `mv pure-ftpd-*/* .`
    `rm -rf pure-ftpd-*/`
    `rm pureftpd.tar.bz2`
    puts "Done!"
  end

  ## Trivial git interface
  def releases_imported
    `git tag -l v*`.split("\n").collect(&:strip)
  end

  def commit! msg
    `git add .`
    `git commit -m "#{msg}"`
  end

  # Trivial
  def tag! release
    `git tag -a v#{release} -m "Release #{release}"`
  end

  ## These methods extract information from an ftp URL
  def hostname_for url
    URI(url).hostname
  end

  def dir_for url
    File.dirname URI(url).path
  end

  def pattern_for url
    File.basename URI(url).path.gsub ":version", "*"
  end

  def regex_for url
    Regexp.new File.basename URI(url).path.gsub('.', '\.').gsub(':version', '(.*)')
  end

  def extract_version_from file, url
    regex = regex_for(url)
    regex.match(file)

    $1
  end
end

PureFTPUpdater.update! # Start the magic!
