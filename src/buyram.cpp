#include <buyram.hpp>

ACTION buyram::ramisrealeos(string slogon) {
   print(slogon);
}

void buyram::handle_transfer(name from, name to, asset quantity, string memo) {
   if (from == _self || to != _self) {
      return;
   }
   require_auth(from);
   eosio::check(get_first_receiver() == "eosio.token"_n && quantity.symbol == symbol(symbol_code("EOS"), 4), "only EOS allowed");
   eosio::check(quantity.amount > 0, "must transfer positive quantity");
   eosio::check(memo.size() <= 12, "memo must be a receiver eos account");
   name receiver = from;
   if (memo.size() > 0) {
      receiver = eosio::name(memo);
      eosio::check(is_account(receiver), "memo must be a receiver eos account");
   }
   action(permission_level { _self, "active"_n }, "eosio"_n, "buyram"_n, make_tuple(_self, receiver, quantity)).send();
   action(permission_level { _self, "active"_n }, receiver, "receiveram"_n, make_tuple()).send();
   action(permission_level { _self, "active"_n }, _self, "ramisrealeos"_n, std::string("RAM is the real EOS!")).send();
}