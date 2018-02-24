# Poco RESTful WebService

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Build Status](https://travis-ci.org/edson-a-soares/poco_restful_webservice.svg?branch=master)](https://travis-ci.org/edson-a-soares/poco_restful_webservice)

### Overview 

This is a totally functional sample of a RESTful API built using [Poco C++ Libraries](https://pocoproject.org).

### Disclaimer

Be aware this is not meant to be a blueprint, the correct way, even worse, the best way to build an API using [Poco C++ Libraries](https://pocoproject.org).
On the contrary, it was built purely for fun and curiosity after I have used this amazing C++ framework in a real project. 
Surely, there are plenty different ways to build a similar project using [Poco C++ Libraries](https://pocoproject.org).
However, I hope this can be useful offering some basic guidance for those trying to build a non trivial application using 
[Poco C++ Libraries](https://pocoproject.org).

### Requirements for running it locally

* **Virtualized environment**

	The development environment is built using virtualization. So, for running it locally you just need to have [Vagrant](https://www.vagrantup.com/docs/installation), [VirtualBox](https://www.virtualbox.org) and [Puppet](https://docs.puppet.com/puppet/3.8/install_debian_ubuntu.html) installed in your computer. 

	Currently, the project has been using the following versions of the tools aforementioned:

	- Vagrant 2.0
	- VirtualBox 5.1
	- Puppet 4.8

* **On your own computer**

	Currently, the project uses the following middleware:

	- CMake 3.7.2
	- GCC-6 and G++-6
	- Google's C++ test framework
	- Poco 1.8.1
	- MySQL

### Running the project

After having **Vagrant**, **VirtualBox** and **Puppet** installed you can run the WebService locally through a few **Ant Tasks** at the root directory of the project as follows:

For making the environment available locally:
```bash
ant -propertyfile dev.properties setup_environment
```

For destroying the environment with everything:
```bash
ant -propertyfile dev.properties destroy_environment
```

For making the database available:
```bash
ant -propertyfile dev.properties create_schema
ant -propertyfile dev.properties init_schema
```

For destroying the database:
```bash
ant -propertyfile dev.properties drop_schema
```

For managing the application development:
```bash
ant -propertyfile dev.properties create_build_directory
ant -propertyfile dev.properties clean_build_directory
ant -propertyfile dev.properties build_project
ant -propertyfile dev.properties compile_project
ant -propertyfile dev.properties run_tests
```

## Usage

After having run the project you will be able to make requests to the API. 
For doing this, use a **Terminal** tool like [cUrl](https://curl.haxx.se) or any **REST Client Tool** like [ARC](https://chrome.google.com/webstore/detail/advanced-rest-client/hgmloofddffdnphfgcellkdfbfbjeloo) or [Postman](https://www.getpostman.com).   
You reach the service at the IP address `192.168.1.100:9090`.

### Running Requests and Responses

For seeing a complete list of API resources and how to make requests and responses consult the [documentation](docs/api/ReferenceGuide.md).

### Standards and Style

This project do not follow any specific **Coding Style Guidelines or Standard**.    
But, it has been influenced by [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html), 
[PPP Style Guide](http://www.stroustrup.com/Programming/PPP-style-rev3.pdf) and [Applied Informatics C++ Coding Style Guide](https://www.appinf.com/download/CppCodingStyleGuide.pdf) itself.  

### Useful links

* [JSON API](http://jsonapi.org)
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/manual/index.html)
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)