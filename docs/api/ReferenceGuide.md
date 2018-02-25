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

```javascript
{  
    "links":{  
        "self":"http://192.168.1.100:0000",
        "polls_url":"http://192.168.1.100:0000/polls?question_id={id}",
        "polls_votes_url":"http://192.168.1.100:0000/polls/votes?question_id={id}"
    },
    "meta":{  
        "copyright":"Copyright 2018 Poco RESTful API",
        "jsonapi":"1.1",
        "lang":[  
            "en-US"
        ]
    }
}
```

### Error response

The **Poco RESTful API** will return error messages as follows:

```javascript
{  
    "error":[  
        {  
            "code":404,
            "description":"This route does not exist.",
            "source":{  
                "pointer":"http://localhost:0000/non-existent-route"
            },
            "type":"Not Found"
        }
    ]
}
```

### HTTP Verbs

Where possible, **Poco REST API** strives to use appropriate HTTP verbs for each action.

|    Verb   | Description                                     |
|:----------|:------------------------------------------------|
| `GET`     | Used for retrieving information from resources. |
| `POST`    | Used for creating resources.                    |
| `PUT`     | Used for replacing/updating resources.          | 
| `DELETE`  | Used for deleting resources.                    |

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

| HTTP Verb | Resource                        | Description                                                  |
|:----------|:--------------------------------|:-------------------------------------------------------------|
| `GET`     | `/`	                          | It shows a **list** with all available resources categories. |
| `POST`    | `/polls`                        | It creates a **new** question. 				                 |
| `GET`     | `/polls?question_id={id}`       |	It **retrieves** a question with its options.                |
| `PUT`     | `/polls?question_id={id}`       |	It **updates** a question with its options.                  |
| `DELETE`  | `/polls?question_id={id}`       |	It **deletes** a question with its options.                  |
| `POST`    | `/polls/votes?question_id={id}` | It performs a **vote** on a question.                        |
| `GET`     | `/polls/votes?question_id={id}` | It **retrieves a list** with all question's options and the amount of votes given to each one of them. |

### Resources

---

### POST polls

It creates a question with the options made available.

### Endpoint

`/polls`

### Request Body

| Parameter   | Description  | Data Type |
|:------------|:-------------|:----------|
| `text`      | **Required**. The main text of the question.                                              | string |
| `label`     | **Optional**. A label to the question.                                                    | string |
| `details`   | **Optional**. Details about the question, if needed.                                      | string |
| `starts_at` | **Required**. The date and time when the question is gonna be make available to be voted. | string. A date and time in the format `yyyy-mm-dd HH:MM:ss` |
| `ends_at`   | **Required**. The date and time when the question is gonna be closed to receiving votes.  | string. A date and time in the format `yyyy-mm-dd HH:MM:ss` |
| `options`   | **Required**. A list with all options to the questions.                                   | array. |

### Sample request

```bash
curl -X POST
    --include http://192.168.1.100:0000/polls
    --header 'Accept-Language: en-US'
    --header 'Accept: application/vnd.api+json' 
    --header 'Content-type: application/vnd.api+json'
    --data '{ 
                "data" : {
                    "attributes" : {
                        "ends_at": "2018-05-01 23:59:00",
                        "starts_at": "2018-04-01 23:59:00",
                        "details": "Details here, please.",
                        "label": "A descriptive short text here.",
                        "text": "Question text here.",
                        "options" : [
                		    { "text" : "First option text."  },
                		    { "text" : "Second option text." },
                		    { "text" : "Third option text."  },
                		    { "text" : "Fourth option text"  }
                        ]
                    }
                }
            }' 
```

### Sample response

```http
HTTP/1.1 201 Created
Date: Wed, 21 Feb 2018 02:19:08 GMT
Connection: Close
Content-Type: application/vnd.api+json; charset=utf-8
Location: http://192.168.1.100:0000/polls?question_id=990689d8-16ad-11e8-b38b-022e0859b13e
Content-Location: http://192.168.1.100:9090/polls?question_id=990689d8-16ad-11e8-b38b-022e0859b13e
```

The `Location` header included in the response points to the new **question** created.

### Error and status codes

The following table lists the status and error codes related to this request.

| Status code | Meaning  |
|:-----------:|----------|
| 201         | Question successfully created |
| 400         | Bad request -- one or more of the parameters was rejected or are not present. |

### GET polls?question_id={id}

It returns a question data with the options embedded.

`{id}` It refers to the ID for the question you want to look up.

### Endpoint

`/polls?question_id={id}`

### Sample request

```bash
curl --get 
    --include http://192.168.1.100:0000/polls?question_id=990689d8-16ad-11e8-b38b-022e0859b13e 
    --header 'Accept-Language: en-US' 
    --header 'Accept: application/vnd.api+json' 
    --header 'Content-type: application/vnd.api+json'
```

### Sample response

```javascript
{
    "data":[
        {
            "attributes":{
                "created_at":"2018-02-21T02:19:08Z",
                "details":"Details here, please.",
                "ends_at":"2018-05-01T23:59:00Z",
                "label":"A descriptive short text here.",
                "last_updated_at":"2018-02-21T02:19:08Z",
                "starts_at":"2018-04-01T23:59:00Z",
                "text":"Question text here."
            },
            "id":"990689d8-16ad-11e8-b38b-022e0859b13e",
            "links":{
                "self":"http://192.168.1.100:9090/polls?question_id=990689d8-16ad-11e8-b38b-022e0859b13e"
            },
            "type":"questions"
        }
    ],
    "included":[
        {
            "data":[
                {
                    "attributes":{
                        "created_at":"2018-02-21T02:19:08Z",
                        "last_updated_at":"2018-02-21T02:19:08Z",
                        "position":1,
                        "text":"First option text."
                    },
                    "id":"990692c0-16ad-11e8-b38b-022e0859b13e",
                    "type":"question_options"
                }
            ]
        },
        {
            "data":[
                {
                    "attributes":{
                        "created_at":"2018-02-21T02:19:08Z",
                        "last_updated_at":"2018-02-21T02:19:08Z",
                        "position":2,
                        "text":"Second option text."
                    },
                    "id":"990694d2-16ad-11e8-b38b-022e0859b13e",
                    "type":"question_options"
                }
            ]
        },
        {
            "data":[
                {
                    "attributes":{
                        "created_at":"2018-02-21T02:19:08Z",
                        "last_updated_at":"2018-02-21T02:19:08Z",
                        "position":3,
                        "text":"Third option text."
                    },
                    "id":"990695d6-16ad-11e8-b38b-022e0859b13e",
                    "type":"question_options"
                }
            ]
        },
        {
            "data":[
                {
                    "attributes":{
                        "created_at":"2018-02-21T02:19:08Z",
                        "last_updated_at":"2018-02-21T02:19:08Z",
                        "position":4,
                        "text":"Fourth option text"
                    },
                    "id":"990696bc-16ad-11e8-b38b-022e0859b13e",
                    "type":"question_options"
                }
            ]
        }
    ]
}
```

The following table describes each item in the JSON response.

| Response Item                              | Description                                 |
|:-------------------------------------------|:--------------------------------------------|
| `data/id`                                  | **ID** of the **question**.                 |
| `data/type`                                | The **type** of the payload; **question**.  |
| `data/links/self`                          | A link to the **question** just found.      |
| `data/attributes/created_at`               | Date and time that the **question** was created. The date and time are in the format `yyyy-mm-dd HH:MM:ss` |
| `data/attributes/details`                  | A detailed description of the **question**. |
| `data/attributes/ends_at`                  | Date and time when the **question** should be out of reach for voting. The date and time are in the format `yyyy-mm-dd HH:MM:ss` |
| `data/attributes/label`                    | A short description of the **question**.    |
| `data/attributes/last_updated_at`          | Last time the **question** was updated. The date and time are in the format `yyyy-mm-dd HH:MM:ss` |
| `data/attributes/starts_at`                | Date and time when the **question** should be available for voting. The date and time are in the format `yyyy-mm-dd HH:MM:ss` |
| `data/attributes/text`                     | The statement of the **question**. |
| `included/data/id`                         | ID of the **option**. |
| `included/data/type`                       | The type of the payload; **question_options**. |
| `included/data/attributes/text`            | The statement of the question's **option**. |
| `included/data/attributes/position`        | The position of the option in the list of the question's **options**. |
| `included/data/attributes/created_at`      | Date and time when the **option** was created. The date and time are in the format `yyyy-mm-dd HH:MM:ss` |
| `included/data/attributes/last_updated_at` | Date and time when the **option** was updated last time. The date and time are in the format `yyyy-mm-dd HH:MM:ss` |

### Error and status codes

The following table lists the status and error codes related to this request.

| Status code | Meaning                                    |
|:-----------:|:-------------------------------------------|
| 200         | Question successfully retrieved.           |
| 400         | Bad request --  ID parameter was rejected. |
| 404         | Not Found -- question wasn't found.        |

