class cmake::install {

    include environment::configure

    $cmake_directory = "cmake-3.7.2"
    $cmake_file_name = "cmake-3.7.2.tar.gz"
    $cmake_url = "https://cmake.org/files/v3.7/cmake-3.7.2.tar.gz"

    exec { "wget-cmake":
        command => "wget $cmake_url --directory-prefix=$environment::configure::home_directory",
        unless  => "test -f $environment::configure::home_directory/$cmake_file_name",
        user    => $environment::configure::home_username,
        group   => $environment::configure::home_group,
        path    => [ "/bin", "/usr/bin" ],
    }

    exec { "uncompress-cmake":
        cwd         => "$environment::configure::home_directory",
        command	    => "tar -xf $cmake_file_name",
        subscribe   => Exec[ "wget-cmake" ],
        user        => $environment::configure::home_username,
        group       => $environment::configure::home_group,
        refreshonly => true,
        logoutput   => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    exec { "configure-cmake":
        cwd         => "$environment::configure::home_directory/$cmake_directory",
        command	    => "sh configure",
        subscribe   => Exec[ "uncompress-cmake" ],
        user        => $environment::configure::home_username,
        group       => $environment::configure::home_group,
        refreshonly => true,
        logoutput   => true,
        timeout     => 1800,
        path        => [ "/bin", "/usr/bin" ],
    }

    exec { "install-cmake":
        cwd         => "$environment::configure::home_directory/$cmake_directory",
        command	    => "sudo make && sudo make install",
        subscribe   => Exec[ "configure-cmake" ],
        refreshonly => true,
        logoutput   => true,
        timeout     => 0,
        path        => [ "/bin", "/usr/bin" ],
    }

}
