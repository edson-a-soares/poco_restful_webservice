# Poco RESTful WebService

This is a totally functional sample of a RESTful API built using [Poco C++ Libraries](https://pocoproject.org). 

## Disclaimer

Be aware this is not meant to be a blueprint, the correct way, even worse, the best way to build an API using [Poco C++ Libraries](https://pocoproject.org).
On the contrary, it was built purely for fun and curiosity after I have used this amazing C++ framework in a real project. 
Surely, there are plenty different ways to build a similar project using [Poco C++ Libraries](https://pocoproject.org).
However, I hope this can be useful offering some basic guidance for those trying to build a non trivial application using 
[Poco C++ Libraries](https://pocoproject.org).

## Requirements

You just need to have [Vagrant](https://www.vagrantup.com/docs/installation) and [Puppet](https://docs.puppet.com/puppet/3.8/install_debian_ubuntu.html) 
installed in your computer to be able to run this application.

## Running the project 

After having **Vagrant** and **Puppet** installed you can execute the WebService through a few commands at the root 
directory of the project as follows:

For making it available in the environment:
```bash
ant setup_environment
ant deploy_project
```

For getting the database ready:
```bash
ant create_schema
ant init_schema
```

For destroying the database:
```bash
ant drop_schema
```

For running it:
```bash
ant run_webservice
```

For destroying everything:
```bash
ant destroy_environment
```

## Usage

After having run the project you will be able to make requests to the WebService. 
For doing this, use the **Terminal** or any **REST Client Tool**. 
[ARC](https://chrome.google.com/webstore/detail/advanced-rest-client/hgmloofddffdnphfgcellkdfbfbjeloo) is a good option.
You reach the service at the IP address `192.168.1.100:9090`.

## HTTP Headers

The HTTP headers used for service.

| HTTP header name  | Description                       |
|:------------------|:----------------------------------|
| `Accept`          | Set to `application/vnd.api+json`. **Required**. | 
| `Content-Type`    | Set to `application/vnd.api+json`. **Required**. | 
| `Accept-Language` | Set to `en-US`. It is the only language supported by now. |  

## Resources

The resources supported by the API:

| resource              | description                       |
|:----------------------|:----------------------------------|
| `/`                   | It returns a list of all resources currently supported by the API |
| `/polls`              | It performs all operations related to Polls supported by the API |
| `/polls/votes`        | It performs all operations related to Polls' votes supported by the API |

## Request and Response

### Resource Root

The resource root presents all the API available resources as a map.

```json
    {
        "links": {
          "self": "http://localhost:0000/",
          "polls_result_url": "http://localhost:0000/polls/votes?question_id={id}",
          "polls_url": "http://localhost:0000/polls?question_id={id}",
          "polls_vote_url": "http://localhost:0000/polls/votes"
        },
        "meta": {
                "copyright": "Copyright 2018 Poco RESTful WebService",
                "jsonapi": "1.1",
            "lang": [
              "en-US"
            ]
        }
    }
```

### Error Responses

```json
{
  "error": [{
      "code": 404,
      "description": "This route does not exist.",
      "source": {
          "pointer": "http://localhost:0000/non-existent-route"
      },
      "type": "Not Found"
  }]
}
```

## Standards and Style

This project did not adopted a specific **Coding Style Guidelines or Standard** until now.    
But, it has been influenced by [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html), 
[PPP Style Guide](http://www.stroustrup.com/Programming/PPP-style-rev3.pdf) and [Applied Informatics C++ Coding Style Guide](https://www.appinf.com/download/CppCodingStyleGuide.pdf) itself.  

## Useful links

* [JSON API](http://jsonapi.org)
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/manual/index.html)
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)
