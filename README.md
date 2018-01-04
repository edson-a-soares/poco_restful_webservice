## Poco RESTful Resource Model

An example of how to build a RESTful WebService using [Poco C++ Libraries](https://pocoproject.org/). 
Specifically, how to organize the WebService resources.

## How to use it

### HTTP headers
The HTTP headers used for the service.

| HTTP header name  | Description                       |
|:------------------|:----------------------------------|
| `Accept`          | Set to `application/vnd.api+json`. **Required**. | 
| `Content-Type`    | Set to `application/vnd.api+json`. **Required**. | 
| `Accept-Language` | Language options like `en-US` or `pt-BR` are shown just as exemples. |  

***

###API Interface

####Resources
The resources supported by the API:

| resource              | description                       |
|:----------------------|:----------------------------------|
| `/`                   | It returns a list of all resources currently supported by the API |

### Request & Response Examples

#### Resource Root 
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

#### Error handling 

```json
{
  "error": [{
      "code": 404,
      "description": "This route does not exist.",
      "source": {
          "pointer": "http://localhost:9000/something"
      },
      "type": "Not Found"
  }]
}
```
