class gtest::install {

    exec { "apt-get-install-libgtest-dev":
        command => "sudo apt-get install libgtest-dev",
        unless  => "test -d /usr/src/gtest",
        path    => [ "/bin", "/usr/bin" ],
    }

    exec { "prepare-gtest-compilation":
        cwd         => "/usr/src/gtest",
        command	    => "sudo cmake .",
        subscribe   => Exec[ "apt-get-install-libgtest-dev" ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    exec { "compile-gtest":
        cwd         => "/usr/src/gtest",
        command	    => "sudo make",
        subscribe   => Exec[ "prepare-gtest-compilation" ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    exec { "install-gtest":
        cwd         => "/usr/src/gtest",
        command	    => "sudo cp *.a /usr/lib",
        require     => Exec[ "compile-gtest" ],
        unless      => "test -f /usr/lib/libgtest.a",
        timeout     => 0,
        path        => [ "/bin", "/usr/bin" ],
    }

}