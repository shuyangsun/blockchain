/**********************************************************************************************************************
 *
 * Copyright (c) 2017-2018 Shuyang Sun
 *
 * License: MIT
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *********************************************************************************************************************/

#ifndef SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_
#define SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_

#include "puppy.hpp"

#include <type_traits>
#include <vector>
#include <iterator>

namespace crypto_puppy {
  std::string OwnerInfo_(Puppy const &puppy);
  std::string ASCIIArtForPuppy_(Puppy const &puppy);

  // ASCII artworks from http://www.chris.com/ascii/index.php?art=animals/dogs

  static std::vector<std::string> puppy_ascii_arts_{
    std::string
  {
    "                             ;\\ \n"
    "                            |' \\ \n"
    "         _                  ; : ; \n"
    "        / `-.              /: : | \n"
    "       |  ,-.`-.          ,': : | \n"
    "       \\  :  `. `.       ,'-. : | \n"
    "        \\ ;    ;  `-.__,'    `-.| \n"
    "         \\ ;   ;  :::  ,::'`:.  `. \n"
    "          \\ `-. :  `    :.    `.  \\ \n"
    "           \\   \\    ,   ;   ,:    (\\ \n"
    "            \\   :., :.    ,'o)): ` `-. \n"
    "           ,/,' ;' ,::\"'`.`---'   `.  `-._ \n"
    "         ,/  :  ; '\"      `;'          ,--`. \n"
    "        ;/   :; ;             ,:'     (   ,:) \n"
    "          ,.,:.    ; ,:.,  ,-._ `.     \\\"\"'/ \n"
    "          '::'     `:'`  ,'(  \\`._____.-'\"' \n"
    "             ;,   ;  `.  `. `._`-.  \\ \n"
    "             ;:.  ;:       `-._`-.\\  \\`. \n"
    "              '`:. :        |' `. `\\  ) \\ \n"
    "      -hrr-      ` ;:       |    `--\\__,' \n"
    "                   '`      ,' \n"
    "                        ,-' \n"
  },
    std::string
  {
    "                     , \n"
    "                ,.  | \\ \n"
    "               |: \\ ; :\\ \n"
    "               :' ;\\| ::\\ \n"
    "                \\ : | `::\\ \n"
    "                _)  |   `:`. \n"
    "              ,' , `.    ;: ; \n"
    "            ,' ;:  ;\"'  ,:: |_ \n"
    "           /,   ` .    ;::: |:`-.__ \n"
    "        _,' _o\\  ,::.`:' ;  ;   . ' \n"
    "    _,-'           `:.          ;""\\, \n"
    " ,-'                     ,:         `-;, \n"
    " \\,                       ;:           ;--._ \n"
    "  `.______,-,----._     ,' ;:        ,/ ,  ,` \n"
    "         / /,-';'  \\     ; `:      ,'/,::.::: \n"
    "       ,',;-'-'_,--;    ;   :.   ,',',;:::::: \n"
    "      ( /___,-'     `.     ;::,,'o/  ,::::::: \n"
    "       `'             )    ;:,'o /  ;\\\" - -:: \n"
    "                      \\__ _,'o ,'         ,:: \n"
    "                         ) `--'       ,..:::: \n"
    "      -hrr-              ; `.        ,::::::: \n"
    "                          ;  ``::.    ::::::: \n"
    "\n"
  },
    std::string
  {
    "        ,--._______,-. \n"
    "       ,','  ,    .  ,_`-. \n"
    "      / /  ,' , _` ``. |  )       `-.. \n"
    "     (,';'\"\"`/ '\"`-._ ` \\ / ______    \\ \n"
    "       : ,o.-`- ,o.  )\\` -'      `---.)) \n"
    "       : , d8b ^-.   '|   `.      `    `. \n"
    "       |/ __:_     `. |  ,  `       `    \\ \n"
    "       | ( ,-.`-.    ;'  ;   `       :    ; \n"
    "       | |  ,   `.      /     ;      :    \\ \n"
    "       ;-'`:::._,`.__),'             :     ; \n"
    "      / ,  `-   `--                  ;     | \n"
    "     /  \\                   `       ,      | \n"
    "    (    `     :              :    ,\\      | \n"
    "     \\   `.    :     :        :  ,'  \\    : \n"
    "      \\    `|-- `     \\ ,'    ,-'     :-.-'; \n"
    "      :     |`--.______;     |        :    : \n"
    "       :    /           |    |         |   \\ \n"
    "       |    ;           ;    ;        /     ; \n"
    "     _/--' |   -hrr-   :`-- /         \\_:_:_| \n"
    "   ,',','  |           |___ \\ \n"
    "   `^._,--'           / , , .) \n"
    "                      `-._,-' \n"
  },
    std::string
  {
    "      __,-----._                       ,-. \n"
    "     ,'   ,-.    \\`---.          ,-----<._/ \n"
    "    (,.-. o:.`    )),\"\\ - ._    ,'         `. \n"
    "   ('\" - ` .\\       \\`:_ )\\  `-; '-._          \\ \n"
    "  ,,-.    \\` ;  :  \\( `-'     ) -._     :   `: \n"
    " (    \\ `._\\\\ ` ;             ;    `    :    ) \n"
    "  \\`.  `-.    __   ,         /  \\        ;, ( \n"
    "   `.`-.___--'  `-          /    ;     | :   | \n"
    "     `-' `-.`--._          '           ;     | \n"
    "           (`--._`.                ;   /\\    | \n"
    "            \\     '                \\  ,  )   : \n"
    "            |  `--::----            \\'   ;  ;| \n"
    "            \\    .__,-      (        )   :  :| \n"
    "             \\    : `------; \\      |    |   ; \n"
    "              \\   :       / , )     |    |  ( \n"
    "     -hrr-     \\   \\      `-^-|     |   / , ,\\ \n"
    "                )  )          | -^- ;   `-^-^' \n"
    "             _,' _ ;          |    | \n"
    "            / , , ,'         /---. : \n"
    "            `-^-^'          (  :  :,' \n"
    "\n"
  }
  };
}


inline crypto_puppy::Puppy::Puppy(PuppyBreed const breed, std::string const &name, std::string const &owner_id):
  owner_id_{ owner_id },
  name_{ name },
  breed_{ breed },
  level_{ PuppyLevel::kBaby }
{ EMPTY_BLOCK }


inline crypto_puppy::Puppy::Puppy(Puppy const & puppy):
  owner_id_{ puppy.OwnerID() },
  name_{ puppy.Name() },
  breed_{ puppy.Breed() },
  level_{ puppy.Level() }
{ EMPTY_BLOCK }


inline crypto_puppy::Puppy::Puppy(Puppy && puppy) :
  owner_id_{ puppy.OwnerID() },
  name_{ puppy.Name() },
  breed_{ puppy.Breed() },
  level_{ puppy.Level() }
{ EMPTY_BLOCK }


inline std::string crypto_puppy::Puppy::OwnerID() const
{
  return owner_id_;
}


inline std::string crypto_puppy::Puppy::Name() const
{
  return name_;
}


inline auto crypto_puppy::Puppy::Breed() const -> PuppyBreed
{
  return breed_;
}


inline auto crypto_puppy::Puppy::Level() const -> PuppyLevel
{
  return level_;
}


inline void crypto_puppy::Puppy::LevelUp()
{
  auto level_raw = static_cast<LevelRawType>(level_);
  ++level_raw;
  level_ = static_cast<PuppyLevel>(level_raw);
}


inline crypto_puppy::Puppy::operator std::string() const
{
  std::string result{ OwnerInfo_(*this) };
  result += "\n";
  result += ASCIIArtForPuppy_(*this);
  return result;
}


template<typename DataT>
inline ssybc::BinaryData crypto_puppy::PuppyBinaryConverter<DataT>::BinaryDataFromData(DataT const & puppy) const
{
  auto level = puppy.Level();
  auto breed = puppy.Breed();
  auto name = puppy.Name();
  auto owner_id = puppy.OwnerID();

  auto level_raw = static_cast<LevelRawType>(level);
  auto breed_raw = static_cast<BreedRawType>(breed);
  ssybc::SizeT name_size = static_cast<ssybc::SizeT>(name.size());
  ssybc::SizeT owner_id_size = static_cast<ssybc::SizeT>(owner_id.size());

  auto level_binary = ssybc::BinaryDataConverterDefault<LevelRawType>().BinaryDataFromData(level_raw);
  auto breed_binary = ssybc::BinaryDataConverterDefault<BreedRawType>().BinaryDataFromData(breed_raw);
  auto name_size_binary = ssybc::BinaryDataConverterDefault<ssybc::SizeT>().BinaryDataFromData(name_size);
  auto name_binary = ssybc::BinaryDataConverterDefault<std::string>().BinaryDataFromData(name);
  auto owner_id_size_binary = ssybc::BinaryDataConverterDefault<ssybc::SizeT>().BinaryDataFromData(owner_id_size);
  auto owner_id_binary = ssybc::BinaryDataConverterDefault<std::string>().BinaryDataFromData(owner_id);

  std::vector<ssybc::BinaryData> bin_data {
      level_binary, breed_binary, name_size_binary, name_binary, owner_id_size_binary, owner_id_binary
  };
  return ssybc::util::ConcatenateMoveDestructive(bin_data);
}


template<typename DataT>
inline auto crypto_puppy::PuppyBinaryConverter<DataT>::DataFromBinaryData(
  ssybc::BinaryData const & binary_data) const -> DataT
{
  ssybc::BinaryData bin_copy{ binary_data.begin(), binary_data.end() };
  auto iter_begin = bin_copy.begin();
  auto iter_end = bin_copy.begin();

  auto level_size = sizeof(LevelRawType);
  auto breed_size = sizeof(BreedRawType);
  auto size_size = sizeof(ssybc::SizeT);

  std::advance(iter_end, level_size);
  auto level_raw = ssybc::BinaryDataConverterDefault<LevelRawType>().DataFromBinaryData(
    ssybc::BinaryData{iter_begin, iter_end}
  );
  iter_begin = iter_end;
  std::advance(iter_end, breed_size);
  auto breed_raw = ssybc::BinaryDataConverterDefault<BreedRawType>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );
  iter_begin = iter_end;
  std::advance(iter_end, size_size);
  auto size_of_name = ssybc::BinaryDataConverterDefault<ssybc::SizeT>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );
  auto name_size = static_cast<std::size_t>(size_of_name);
  iter_begin = iter_end;
  std::advance(iter_end, name_size);
  std::string name = ssybc::BinaryDataConverterDefault<std::string>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );
  iter_begin = iter_end;
  std::advance(iter_end, size_size);
  auto size_of_owner_id = ssybc::BinaryDataConverterDefault<ssybc::SizeT>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );
  auto owner_id_size = static_cast<std::size_t>(size_of_owner_id);
  iter_begin = iter_end;
  std::advance(iter_end, owner_id_size);
  std::string owner_id = ssybc::BinaryDataConverterDefault<std::string>().DataFromBinaryData(
    ssybc::BinaryData{ iter_begin, iter_end }
  );

  auto breed = static_cast<PuppyBreed>(breed_raw);
  auto level = static_cast<PuppyLevel>(level_raw);
  
  Puppy result{ breed, name, owner_id };
  for (LevelRawType i{ 0 }; i < level_raw; ++i) {
    result.LevelUp();
  }
  return result;
}


std::string crypto_puppy::PuppyBreedDescription(PuppyBreed const breed)
{
  switch (breed) {
  case PuppyBreed::kHusky:
    return "Husky";
  case PuppyBreed::kBulldog:
    return "Bulldog";
  default:
    return "Unknown breed";
  }
}


std::string crypto_puppy::PuppyLevelDescription(PuppyLevel const level)
{
  switch (level) {
  case PuppyLevel::kBaby:
    return "Baby";
  case PuppyLevel::kAdult:
    return "Adult";
  default:
    return "Unknown level";
  }
}


std::string crypto_puppy::OwnerInfo_(Puppy const &puppy)
{
  std::string result{ puppy.OwnerID() };
  result += "'s ";
  result += puppy.Name();
  result += " (";
  result += PuppyLevelDescription(puppy.Level());
  result += " ";
  result += PuppyBreedDescription(puppy.Breed());
  result += ")!";
  return result;
}

std::string crypto_puppy::ASCIIArtForPuppy_(Puppy const &puppy)
{
  auto breed_raw = static_cast<BreedRawType>(puppy.Breed());
  auto breed_max = static_cast<BreedRawType>(PuppyBreed::kPuppyBreedCount);
  auto level_raw = static_cast<BreedRawType>(puppy.Level());

  std::size_t index = static_cast<std::size_t>(breed_raw * breed_max + level_raw);
  return puppy_ascii_arts_[index];
}


#endif  // SSYBC_SAMPLES_SAMPLE_CPU_CRYPTO_PUPPY_PUPPY_IMPL_HPP_
