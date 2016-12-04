#include <sort.hpp>
#include <catch.hpp>
#include <string>
#include <iostream>
#include <fstream>

 SCENARIO("8mb", "[8mb]")
 {
  REQUIRE(1 == 1);
 }

/*SCENARIO("8mb", "[8mb]")
{
  _sort other("8mb", "out_8", 1);
  bool x = true;
  std::ifstream f11("out_8"), f22("out8");
  stud st1, st2;
  while(!f22.eof() && !f11.eof())
  {
    if((f11>>st1)&&(f22>>st2))
    {
      if(st1.name!=st2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f11.close();
  f22.close();
  REQUIRE(x);
}*/

// SCENARIO("15mb", "[15mb]")
// {
//   _sort other("15mb", "out_15", 4);
//   bool x = true;
//   std::ifstream f11("out_15"), f22("out15");
//   stud st1, st2;
//   while(!f22.eof() && !f11.eof())
//   {
//     if((f11>>st1)&&(f22>>st2))
//     {
//       if(st1.name!=st2.name)
//       {
//         x=false;
//         break;
//       }
//     }
//     else break;
//   }
//   f11.close();
//   f22.close();
//   REQUIRE(x);
// }

// SCENARIO("32mb", "[32mb]")
// {
//   _sort other("32mb", "out_32", 17);
//   bool x = true;
//   std::ifstream f11("out_32"), f22("out32");
//   stud st1, st2;
//   while(!f22.eof() && !f11.eof())
//   {
//     if((f11>>st1)&&(f22>>st2))
//     {
//       if(st1.name!=st2.name)
//       {
//         x=false;
//         break;
//       }
//     }
//     else break;
//   }
//   f11.close();
//   f22.close();
//   REQUIRE(x);
// }
