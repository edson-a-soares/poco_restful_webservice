#include "Adapter/Http/CORSConfiguration.h"

namespace Http {


    CORSConfiguration::CORSConfiguration(std::unique_ptr<Foundation::IO::JsonFileReaderInterface> fileReader)
        : _headers(),
          _fileReader(std::move(fileReader))
    {}

    std::map<std::string, std::string> CORSConfiguration::headers()
    {
        _headers["Access-Control-Allow-Origin"]      = _fileReader->fetch("allow_origins");
        _headers["Access-Control-Allow-Credentials"] = _fileReader->fetch("allow_credentials");
        _headers["Access-Control-Request-Method"]    = _fileReader->fetch("allow_http_methods");
        _headers["Access-Control-Request-Headers"]   = _fileReader->fetch("allow_http_headers");

        return _headers;
    }


}
