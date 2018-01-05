# Poco RESTful Resource Model

It is an example of how to build a RESTful WebService using [Poco C++ Libraries](https://pocoproject.org). 
Specifically, how to structure and organize its resources.

## Requirements

You need to have [Vagrant](https://www.vagrantup.com/docs/installation), [Puppet](https://docs.puppet.com/puppet/3.8/install_debian_ubuntu.html), 
and [Ant](http://ant.apache.org/manual/install.html) with [SSHEXEC](https://ant.apache.org/manual/Tasks/sshexec.html) 
extension installed in your computer.

## Running the project 

After having **Vagrant** and **Ant** installed you can execute the WebService through a few commands at the root 
directory of the project as follows:

For making it available in the environment:
```shell
ant setup_environment
ant deploy_project
```

For running it:
```shell
ant run_webservice
```

For destroying the everything:
```shell
ant destroy_environment
```

## Usage

After having run the project you will be able to make requests to the WebService. 
For doing this, use the **Terminal** or any **REST Client Tool**. 
[ARC](https://chrome.google.com/webstore/detail/advanced-rest-client/hgmloofddffdnphfgcellkdfbfbjeloo) is a good option.
You reach the service at the IP address `192.168.1.100:9000`.

## HTTP Headers

The HTTP headers used for the service.

| HTTP header name  | Description                       |
|:------------------|:----------------------------------|
| `Accept`          | Set to `application/vnd.api+json`. **Required**. | 
| `Content-Type`    | Set to `application/vnd.api+json`. **Required**. | 
| `Accept-Language` | Language options like `en-US` or `pt-BR` are shown just as examples. |  

## Resources

The resources supported by the API:

| resource              | description                       |
|:----------------------|:----------------------------------|
| `/`                   | It returns a list of all resources currently supported by the API |

## Request and Response

### Resource Root

The resource root presents all the API available resources as a map.

```json
    {
        "links": {
          "self": "http://localhost:9000/"
        },
        "meta": {
            "lang": [
              "en-US",
              "pt-BR"
            ],
            "version": "1.0"
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
          "pointer": "http://localhost:9000/non-existent-route"
      },
      "type": "Not Found"
  }]
}
```

## Useful links

* [JSON API](http://jsonapi.org)