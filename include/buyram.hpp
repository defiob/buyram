#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
using namespace eosio;
using namespace std;

CONTRACT buyram : public contract {
public:
   using contract::contract;

   [[eosio::action]]
   void ramisrealeos(string slogon);

   [[eosio::on_notify("*::transfer")]]
   void handle_transfer(name from, name to, asset quantity, string memo);
};