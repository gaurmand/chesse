#ifndef CHESS_ATTACKS_H
#define CHESS_ATTACKS_H

#include "square.h"
#include "bitboard.h"
#include "common.h"

#include <array>

namespace Chess::Attacks
{

//=============================================================================
using BitboardArray = std::array<Bitboard, NUM_SQUARES>;
using BitboardArrayPerRay = std::array<BitboardArray, kNumRayDirs>;
using BitboardArrayPerColour = std::array<BitboardArray, kNumColors>;

//=============================================================================
constexpr void setIfValid(Bitboard& bb, int target)
{
   if (isValid(target))
   {
      bb.set(target);
   }
}

//=============================================================================
constexpr BitboardArray initKnightAttacks()
{
   BitboardArray atk;
   for (Square sq = Sq::a1; sq <= Sq::h8; ++sq)
   {
      for (int hook : hooks)
      {
         setIfValid(atk[sq], sq + hook);
      }
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArray initKingAttacks()
{
   BitboardArray atk;
   for (Square sq = Sq::a1; sq <= Sq::h8; ++sq)
   {
      for (int ray : rays)
      {
         setIfValid(atk[sq], sq + ray);
      }
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArray initPawnAttacks(int c)
{
   const int kNumPawnAtkRays = 2;
   constexpr std::array<std::array<int, kNumPawnAtkRays>, kNumColors> atkRays = {rays[NW], rays[NE], rays[SW], rays[SE]};

   BitboardArray atk;
   for (Square sq = Sq::a1; sq <= Sq::h8; ++sq)
   {
      for (const int ray : atkRays[c])
      {
         setIfValid(atk[sq], sq + ray);
      }
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArrayPerColour initPawnAttacks()
{
   BitboardArrayPerColour atk;
   for (int c = 0; c < kNumColors; ++c)
   {
      atk[c] = initPawnAttacks(c);
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArray initPawnPushes(int c)
{
   const int kNumPawnPushRays = 1;
   constexpr std::array<std::array<int, kNumPawnPushRays>, kNumColors> pushRays = {rays[N], rays[S]};

   BitboardArray atk;
   for (Square sq = Sq::a1; sq <= Sq::h8; ++sq)
   {
      for (const int ray : pushRays[c])
      {
         setIfValid(atk[sq], sq + ray);
      }
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArrayPerColour initPawnPushes()
{
   BitboardArrayPerColour atk;
   for (int c = 0; c < kNumColors; ++c)
   {
      atk[c] = initPawnPushes(c);
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArrayPerColour initPawnDoublePushes()
{
   BitboardArrayPerColour res;
   for (Square sq = Sq::a2; sq <= Sq::h2; ++sq)
   {
      const Square to = sq + rays[N] + rays[N];
      res[Color::White][sq].set(to);
   }
   for (Square sq = Sq::a7; sq <= Sq::h7; ++sq)
   {
      const Square to = sq + rays[S] + rays[S];
      res[Color::Black][sq].set(to);
   }
   return res;  
}

//=============================================================================
constexpr BitboardArray initRays(int ray)
{
   BitboardArray atk;
   for (Square sq = Sq::a1; sq <= Sq::h8; ++sq)
   {
      for (Square to = sq + ray; isValid(to); to += ray)
      {
         atk[sq].set(to);
      }
   }
   return atk;  
}

//=============================================================================
constexpr BitboardArrayPerRay initRayAttacks()
{
   BitboardArrayPerRay res;
   for (int dir = 0; dir < kNumRayDirs; ++dir)
   {
      res[dir] = initRays(rays[dir]);
   }
   return res;
}

//=============================================================================
constexpr BitboardArray knight             = initKnightAttacks();
constexpr BitboardArray king               = initKingAttacks();
constexpr BitboardArrayPerColour pawn      = initPawnAttacks();
constexpr BitboardArrayPerColour pawnPush  = initPawnPushes();
constexpr BitboardArrayPerColour pawnDPush = initPawnDoublePushes();
constexpr BitboardArrayPerRay ray          = initRayAttacks();

}  // namespace Chess

#endif   // CHESS_ATTACKS_H