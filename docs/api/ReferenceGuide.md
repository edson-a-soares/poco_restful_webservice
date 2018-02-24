# Poco RESTful API Reference Guide

### Overview

This document describes the resources supported by the **Poco REST API**.

### Table of contents

- [Root endpoint](#root-endpoint)   
- [Error response](#error-response)    
- [HTTP Verbs](#http-verbs)    
- [HTTP Headers](#http-headers)    
- [Json API](#json-api)    
- [API Reference](#api-reference)    

### Root endpoint

You can issue a **GET** request to the root endpoint to get all the endpoint categories that the **Poco REST API** supports:

```bash
curl http://192.168.1.100:0000
```

You'll get a response like this:

```json
    {
        "links": {
          "self": "http://192.168.1.100:0000",
          "polls_url": "http://192.168.1.100:0000/polls?question_id={id}",
          "polls_votes_url": "http://192.168.1.100:0000/polls/votes?question_id={id}"
        },
        "meta": {
                "copyright": "Copyright 2018 Poco RESTful API",
                "jsonapi": "1.1",
            "lang": [
              "en-US"
            ]
        }
    }
```

### Error response

The **Poco RESTful API** will return error messages as follows:

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

### HTTP Verbs

Where possible, **Poco REST API** strives to use appropriate HTTP verbs for each action.

|    Verb   | Description                    |
|:----------|:-------------------------------|
| `GET`     | Used for retrieving resources. | 
| `POST`    | Used for creating resources.   |
| `PUT`     | Used for replacing resources.  |  
| `DELETE`  | Used for deleting resources.   | 


### HTTP Headers

The most basic **HTTP** headers used for all requests to the **API**.

| HTTP header name  | Description                                               |
|:------------------|:----------------------------------------------------------|
| `Accept`          | Set to `application/vnd.api+json`. **Required**.          | 
| `Content-Type`    | Set to `application/vnd.api+json`. **Required**.          | 
| `Accept-Language` | Set to `en-US`. It is the only language supported by now. |  

### Json API

The **Poco RESTful API** use the [Json API](http://jsonapi.org) as its JSON default and only supported format.

## API Reference

The following resources are currently supported by the API:

| HTTP Verb | Resource | Description                                   |
|----------:|----------|-----------------------------------------------|
| `GET`     | /		   | It shows a list with all available resources. |
| `POST`    | /polls   | It creates a new question. |
| `GET`     | /polls?question_id={id} |	It retrieves a question with its options. |
| `PUT`     | /polls?question_id={id} |	It updates a question with its options.   |
| `DELETE`  | /polls?question_id={id} |	It deletes a question with its options.   |
| `POST`    | /polls/votes?question_id={id} | It performs a vote in a question.   |
| `GET`     | /polls/votes?question_id={id} | It retrieves a list with all question's options and the amount of votes given to each one of them. |
