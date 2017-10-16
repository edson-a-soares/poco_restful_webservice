class poco::install {

    include environment::configure

    $poco_library_url = "https://pocoproject.org/releases/poco-1.7.8/poco-1.7.8-all.tar.gz"

    exec { "wget-poco":
        command => "wget $poco_library_url --directory-prefix=$environment::configure::home_directory",
        unless  => "test -d /usr/local/include/Poco",
        timeout => 0,
        path    => [ "/bin", "/usr/bin" ],
    }

    exec { "uncompress-poco":
        cwd         => "$environment::configure::home_directory",
        command	    => "tar -xf poco-1.7.8-all.tar.gz",
        user        => $environment::configure::home_username,
        group       => $environment::configure::home_group,
        subscribe   => Exec[ "wget-poco" ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    exec { "configure-poco":
        cwd         => "$environment::configure::home_directory/poco-1.7.8-all",
        command	    => "sudo sh configure --no-tests --no-samples --minimal",
        subscribe   => Exec[ "uncompress-poco" ],
        user        => $environment::configure::home_username,
        group       => $environment::configure::home_group,
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    exec { "install-poco":
        cwd         => "$environment::configure::home_directory/poco-1.7.8-all",
        command	    => "sudo make && sudo make install",
        subscribe   => Exec[ "configure-poco" ],
        refreshonly => true,
        timeout     => 1800,
        logoutput   => true,
        path        => [ "/bin", "/usr/bin" ],
    }

}
