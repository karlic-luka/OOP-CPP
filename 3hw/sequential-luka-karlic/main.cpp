#include <iostream>
#include <cassert>
#include "sequential.h"

using namespace std;

bool testirajLUCache()
{
   LUCache<3> mapa;
   //provjeri radi li size i insert
   assert(mapa.size() == 0);
   mapa.insert(make_pair("b", 1));
   assert(mapa.size() == 1);
   mapa.insert(make_pair("a", 1));
   assert(mapa.size() == 2);
   mapa.insert(make_pair("c", 1));
   assert(mapa.size() == 3);
   mapa.insert(make_pair("a", 2));
   assert(mapa.size() == 3);
   assert(mapa.getKey(0) == "a");
   assert(mapa.getKey(1) == "b");
   assert(mapa.getKey(2) == "c");
   mapa.insert(make_pair("d", 1)); //maknut ce zadnji element
   assert(mapa.getKey(2) == "d");

   //provjeri radi li find
   auto trazi = mapa.find("a");
   assert(trazi.has_value() == true);
   trazi = mapa.find("f");
   assert(trazi.has_value() == false);
   trazi = mapa.find("a");
   assert(trazi.value() == 1); //ne smije biti 2(pokusao naknadno dodati ("a", 2))

   //provjeri radi li erase
   assert(mapa.size() == 3);
   mapa.erase("a");
   trazi = mapa.find("a");
   assert(trazi.has_value() == false);
   assert(mapa.size() == 2);
   assert(mapa.getKey(0) == "b");
   assert(mapa.getKey(1) == "d");
   mapa.erase("b");
   mapa.erase("c");
   assert(mapa.size() == 1);
   mapa.erase("d");
   assert(mapa.size() == 0);
   return true;
}
bool testirajMap()
{
   Map mapa;
   assert(mapa.size() == 0);
   mapa.insert(make_pair("b", 1));
   mapa.insert(make_pair("b", 2));
   mapa.insert(make_pair("a", 1));
   mapa.insert(make_pair("c", 1));
   assert(mapa.size() == 3);
   assert(mapa.find("b").has_value() == true);
   assert(mapa.find("b").value() == 1);

   assert(mapa.find("z").has_value() == false);
   assert(mapa.erase("a") == true);
   assert(mapa.size() == 2);
   assert(mapa.find("a").has_value() == false);
   assert(mapa.erase("g") == false);

   assert(mapa.erase("b") == true);
   assert(mapa.find("b").has_value() == false);
   assert(mapa.size() == 1);

   assert(mapa.erase("c") == true);
   assert(mapa.find("c").has_value() == false);
   assert(mapa.size() == 0);
   //to je manje vise to
   return true;
}

int main(int, char **)
{
   // Ovdje dolaze vaši testovi
   if (testirajLUCache())
      cout << "LUCache testovi prolaze!" << endl;
   if (testirajMap())
      cout << "Map testovi prolaze! Mozes predahnuti" << endl;
}
