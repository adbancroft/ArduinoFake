#pragma once

#include "StreamFake.h"
#include "arduino/Client.h"

using ClientFake = Client;

class ClientFakeProxy : public StreamFakeProxy<ClientFake>
{
public:
    ClientFakeProxy(ClientFake* fake) : StreamFakeProxy<ClientFake>(fake)
    {
    }
};
