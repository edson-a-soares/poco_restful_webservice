
    include mysql
    include mysql::server
    include mysql::client

    include environment
    include environment::configure

    include gcc
    include gcc::install

    include poco
    include poco::install

    include cmake
    include cmake::install

    Class[ "environment::configure" ]   ->
    Class[ "gcc::install" ]             ->
    Class[ "poco::install" ]            ->
    Class[ "cmake::install" ]           ->

    mysql::database { "webservice":
      schema    => 'webservice',
      password  => 'poco'
    }
