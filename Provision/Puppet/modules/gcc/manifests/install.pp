class gcc::install {

    exec { "apt-add-repository":
        command	=> "sudo apt-add-repository ppa:ubuntu-toolchain-r/test",
        unless  => "test -f /etc/apt/sources.list.d/ubuntu-toolchain-r-test-trusty.list",
        path    => [ "/bin", "/usr/bin" ],
    }

    exec { "apt-update":
        command	    => "sudo apt-get update --yes --force-yes",
        subscribe   => Exec[ "apt-add-repository" ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

    package { "gcc-4.9":
        ensure	=> installed,
        require => Exec["apt-add-repository"]
    }

    package { "g++-4.9":
        ensure	=> installed,
        require	=> Package["gcc-4.9"]
    }

    exec { "update-alternatives":
        command	    => "sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9",
        subscribe   => [
            Package[ "gcc-4.9" ],
            Package[ "g++-4.9" ]
        ],
        refreshonly => true,
        path        => [ "/bin", "/usr/bin" ],
    }

}
