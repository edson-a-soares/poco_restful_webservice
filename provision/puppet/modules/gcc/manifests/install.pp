class gcc::install {

    exec { "apt-add-repository":
        command	=> "sudo apt-add-repository ppa:ubuntu-toolchain-r/test",
        unless  => "test -f /etc/apt/sources.list.d/ubuntu-toolchain-r-ubuntu-test-xenial.list",
        path    => [ "/bin", "/usr/bin" ],
    }

    exec { "apt-update":
        command	    => "sudo apt-get update --yes --force-yes",
        subscribe   => Exec[ "apt-add-repository" ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    package { "gcc-snapshot":
        ensure	=> installed,
        require => Exec["apt-add-repository"]
    }

    package { "gcc-6":
        ensure	=> installed,
        require => Exec["apt-add-repository"]
    }

    package { "g++-6":
        ensure	=> installed,
        require	=> Package["gcc-6"]
    }

    exec { "update-alternatives":
        command	    => "sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6",
        subscribe   => [
            Package[ "gcc-6" ],
            Package[ "g++-6" ]
        ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

}
