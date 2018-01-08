class environment::configure {

    $home_group     = "ubuntu"
    $home_username  = "ubuntu"
    $mysql_username = "developer"
    $mysql_password = "abc12345"
    $home_directory = "/home/$home_username"

    exec { "create-homeuser":
        command => "sudo adduser $instance_username",
        path    => [ "/usr/bin", "/bin" ],
        unless  => "test -d $home_directory"
    }

    file { "/etc/profile.d/append-usr-libraries-to-library-path.sh":
        ensure => present,
        mode    => "644",
        content => "export LD_LIBRARY_PATH=\"/usr/local/lib:\$LD_LIBRARY_PATH\"",
    }

    package { "build-essential":
        ensure	=> installed,
    }

    package { "git":
        ensure	=> installed,
    }

    package { "pkg-config":
        ensure	=> installed,
    }

    package { "libcurl4-gnutls-dev":
        ensure	=> installed,
    }

    package { "libarchive-dev":
        ensure	=> installed,
    }

    package { "libreadline6-dev":
        ensure	=> installed,
    }

    package { "libncurses-dev":
        ensure	=> installed,
    }

}
