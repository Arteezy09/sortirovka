#include <sort.hpp>
#include <catch.hpp>
#include <string>
#include <iostream>
#include <fstream>

/* SCENARIO("8mb", "[8mb]")
 {
  REQUIRE(1 == 1);
 }*/

SCENARIO("8mb", "[8mb]")
{
  File_sort other("8mb", "out_8", 1);
  bool x = true;
  std::ifstream f1("out_8"), f2("out8");
  Data s1, s2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>s1)&&(f2>>s2))
    {
      if(s1.name!=s2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}

// SCENARIO("15mb", "[15mb]")
// {
//   File_sort other("15mb", "out_15", 4);
//   bool x = true;
//   std::ifstream f1("out_15"), f2("out15");
//   Data s1, s2;
//   while(!f2.eof() && !f1.eof())
//   {
//     if((f1>>s1)&&(f2>>s2))
//     {
//       if(s1.name!=s2.name)
//       {
//         x=false;
//         break;
//       }
//     }
//     else break;
//   }
//   f1.close();
//   f2.close();
//   REQUIRE(x);
// }

// SCENARIO("32mb", "[32mb]")
// {
//   File_sort other("32mb", "out_32", 17);
//   bool x = true;
//   std::ifstream f1("out_32"), f2("out32");
//   Data s1, s2;
//   while(!f2.eof() && !f1.eof())
//   {
//     if((f1>>s1)&&(f2>>s2))
//     {
//       if(s1.name!=s2.name)
//       {
//         x=false;
//         break;
//       }
//     }
//     else break;
//   }
//   f1.close();
//   f2.close();
//   REQUIRE(x);
// }
