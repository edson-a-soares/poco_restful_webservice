## Introduction

**Poco RESTful Web Service** is an completely functional Web Service developed in C++ using [Poco C++ Libraries](https://pocoproject.org/). 
It is basically an example of how to develop a **RESTful Web Service** in C++ using **Poco** and it was based in a real world web service
developed for allowing service providers perform provisioning operations under [EPP Protocol](https://en.wikipedia.org/wiki/Extensible_Provisioning_Protocol).

## How to use it

#### Starting the Poco RESTful Web Service at Command Line

For installing the application completely perform the steps as follows.

> git clone https://github.com/edson-a-soares/poco_restful_webservice.git 
> cd poco_restful_webservice 
> sudo cmake . 
> sudo make 
> sudo make install 

Now, just type **poco_restful_webservice** at the Command Line for using the service.

However, you can start the service even without installing it performing the steps as follows.

> git clone https://github.com/edson-a-soares/poco_restful_webservice.git 
> cd poco_restful_webservice 
> sudo cmake . 
> sudo make 
> cd poco_restful_webservice/Launcher/bin

Now, just type **./poco_restful_webservice** at the Command Line for using the service.

Anyway, after having been started, the application is going to show that the service has been started as follows:

> Poco Restful Web Service started and running.
> Type http://localhost:9000 to use it or type CRLT+C to finish it.

#### Stopping the Poco RESTful Web Service at Command Line

As the very message warns after the service has been started, for stopping the service, you should just type **CTRL+C**.  
Therefore, It is going to show that the service has been stopped as follows:

> Poco Restful Web Service stopped. 
> Goodbye.   


### Useful links ###

* [Citerus](https://github.com/citerus/dddsample-core)
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)
* [EPP Registro.br](https://registro.br/tecnologia/provedor-hospedagem.html?secao=epp)

### References ###

* **Evans, Eric**, [Domain-Driven Design: Tackling Complexity in the Heart of Software](https://www.amazon.com.br/Domain-Driven-Design-Tackling-Complexity-Software/dp/0321125215)
