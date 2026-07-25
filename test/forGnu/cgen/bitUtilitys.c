#define OPENCF_FOR_GNU
#include "cfrost/cgen/bitUtilitys.h"
#include "cfrost.h"

/**
 * @file bitUtilitys.c
 * @brief Comprehensive OCF_TEST suite for bitUtilitys library
 * @details OCF_TESTs all bit manipulation operations:
 *          - ocf_get_*bit() - retrieve bit values
 *          - ocf_set_*bit() - ocf_set bits to 1
 *          - ocf_reset_*bit() - clear bits to 0
 *          - ocf_toggle_*bit() - flip bit values
 *          - ocf_xchg_*bit() - exchange/swap bits
 *          - ocf_count_*bit() - ocf_count ocf_set/unocf_set bits
 *          Covers uint8, int8, uint16, int16, uint32, int32, uint64, int64
 */

OCF_TEST_MAIN(cgen: bitUtilitys);

  // ==================== 8-BIT UNSIGNED INTEGER OCF_TESTS ====================
  //  testing: ocf_get_u8bit, ocf_set_u8bit, ocf_reset_u8bit, ocf_toggle_u8bit, ocf_xchg_u8bit, ocf_count_u8bit
  
  uint8_t value_1 = 8;                     // value_1: 0000-1000
  OCF_TEST_EQU(ocf_get_u8bit(value_1, 0), false);     // bit 0 should be 0
  OCF_TEST_EQU(ocf_get_u8bit(value_1, 3), true);      // bit 3 should be 1
  OCF_TEST_EQU(ocf_get_u8bit(value_1, 7), false);     // bit 7 should be 0
  
  value_1 = ocf_set_u8bit(value_1, 0);         // value_1: 0000-1001
  OCF_TEST_EQU(ocf_get_u8bit(value_1, 0), true);      // bit 0 should now be 1
  
  value_1 = ocf_set_u8bit(value_1, 7);         // value_1: 1000-1001
  OCF_TEST_EQU(ocf_get_u8bit(value_1, 7), true);      // bit 7 should now be 1
  
  uint8_t value_2 = 99;                    // value_2: 0110-0011
  OCF_TEST_EQU(ocf_get_u8bit(value_2, 6), true);      // bit 6 should be 1
  
  value_2 = ocf_reset_u8bit(value_2, 6);       // value_2: 0010-0011
  OCF_TEST_EQU(ocf_get_u8bit(value_2, 6), false);     // bit 6 should be cleared
  
  value_2 = ocf_set_u8bit(value_2, 7);         // value_2: 1010-0011
  OCF_TEST_EQU(ocf_get_u8bit(value_2, 7), true);      // bit 7 should be ocf_set
  
  value_2 = ocf_set_u8bit(value_2, 3);         // value_2: 1010-1011
  OCF_TEST_EQU(ocf_get_u8bit(value_2, 3), true);      // bit 3 should be ocf_set
  
  value_2 = ocf_reset_u8bit(value_2, 1);       // value_2: 1010-1001
  OCF_TEST_EQU(ocf_get_u8bit(value_2, 1), false);     // bit 1 should be cleared

  uint8_t value_3 = 16;                    // value_3: 0001-0000
  OCF_TEST_EQU(ocf_get_u8bit(value_3, 0), false);     // bit 0 should be 0
  OCF_TEST_EQU(ocf_get_u8bit(value_3, 4), true);      // bit 4 should be 1
  
  value_3 = ocf_xchg_u8bit(value_3, 4, 0);     // value_3: 0000-0001, exchange bits 4 and 0
  OCF_TEST_EQU(ocf_get_u8bit(value_3, 0), true);      // bit 0 should be 1
  OCF_TEST_EQU(ocf_get_u8bit(value_3, 4), false);     // bit 4 should be 0
  
  value_3 = ocf_reset_u8bit(value_3, 0);       // value_3: 0000-0000
  OCF_TEST_EQU(value_3, 0);                       // value should be 0

  uint8_t value_4 = 35;                    // value_4: 0010-0011
  OCF_TEST_EQU(ocf_get_u8bit(value_4, 0), true);      // bit 0 should be 1
  OCF_TEST_EQU(ocf_get_u8bit(value_4, 7), false);     // bit 7 should be 0
  
  value_4 = ocf_toggle_u8bit(value_4, 0);      // value_4: 0010-0010, ocf_toggle bit 0
  OCF_TEST_EQU(ocf_get_u8bit(value_4, 0), false);     // bit 0 should be 0
  
  value_4 = ocf_toggle_u8bit(value_4, 7);      // value_4: 1010-0010, ocf_toggle bit 7
  OCF_TEST_EQU(ocf_get_u8bit(value_4, 7), true);      // bit 7 should be 1
  
  value_4 = ocf_xchg_u8bit(value_4, 5, 0);     // value_4: 1000-0011
  OCF_TEST_EQU(ocf_get_u8bit(value_4, 5), false);     // bit 5 should be 0

  // OCF_TEST ocf_count_u8bit for various patterns
  OCF_TEST_EQU(ocf_count_u8bit(value_1, true), 3);    // value_1 has 3 ocf_set bits
  OCF_TEST_EQU(ocf_count_u8bit(value_2, true), 4);    // value_2 has 4 ocf_set bits
  OCF_TEST_EQU(ocf_count_u8bit(value_3, true), 0);    // value_3 has 0 ocf_set bits
  OCF_TEST_EQU(ocf_count_u8bit(value_3, false), 8);   // value_3 has 8 unocf_set bits
  OCF_TEST_EQU(ocf_count_u8bit(value_4, false), 5);   // value_4 has 5 unocf_set bits

  // ==================== 8-BIT SIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_8bit, ocf_set_8bit, ocf_reset_8bit, ocf_toggle_8bit, ocf_xchg_8bit, ocf_count_8bit
  
  int8_t value_5 = -2;                     // value_5: 1111-1110 (two's complement)
  OCF_TEST_EQU(ocf_get_8bit(value_5, 0), false);      // bit 0 should be 0
  
  value_5 = ocf_set_8bit(value_5, 0);
  OCF_TEST_EQU(ocf_get_8bit(value_5, 0), true);       // bit 0 should be 1
  OCF_TEST_EQU(ocf_get_8bit(value_5, 5), true);       // bit 5 should be 1
  
  value_5 = ocf_toggle_8bit(value_5, 5);
  OCF_TEST_EQU(ocf_get_8bit(value_5, 5), false);      // bit 5 should be ocf_toggled to 0
  OCF_TEST_EQU(ocf_count_8bit(value_5, true), 7);     // should have 7 ocf_set bits

  int8_t value_6 = 88;                     // value_6: 0101-1000
  OCF_TEST_EQU(ocf_get_8bit(value_6, 3), true);       // bit 3 should be 1
  OCF_TEST_EQU(ocf_get_8bit(value_6, 4), true);       // bit 4 should be 1
  
  value_6 = ocf_xchg_8bit(value_6, 3, 1);      // exchange bits 3 and 1
  OCF_TEST_EQU(ocf_get_8bit(value_6, 1), true);       // bit 1 should be 1
  OCF_TEST_EQU(ocf_get_8bit(value_6, 3), false);      // bit 3 should be 0
  
  value_6 = ocf_toggle_8bit(value_6, 4);
  OCF_TEST_EQU(ocf_get_8bit(value_6, 4), false);      // bit 4 should be ocf_toggled to 0
  
  value_6 = ocf_reset_8bit(value_6, 1);
  OCF_TEST_EQU(ocf_get_8bit(value_6, 1), false);      // bit 1 should be 0

  // ==================== 16-BIT UNSIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_u16bit, ocf_set_u16bit, ocf_reset_u16bit, ocf_toggle_u16bit, ocf_xchg_u16bit, ocf_count_u16bit
  
  uint16_t value_7 = 3380;                 // Binary: 1101001110100
  OCF_TEST_EQU(ocf_get_u16bit(value_7, 7), false);    // bit 7 should be 0
  OCF_TEST_EQU(ocf_get_u16bit(value_7, 8), true);     // bit 8 should be 1
  
  value_7 = ocf_toggle_u16bit(value_7, 7);
  OCF_TEST_EQU(ocf_get_u16bit(value_7, 7), true);     // bit 7 should be ocf_toggled to 1
  
  value_7 = ocf_reset_u16bit(value_7, 8);
  OCF_TEST_EQU(ocf_get_u16bit(value_7, 8), false);    // bit 8 should be 0
  OCF_TEST_EQU(ocf_get_u16bit(value_7, 1), false);    // bit 1 should be 0
  
  value_7 = ocf_set_u16bit(value_7, 1);
  OCF_TEST_EQU(ocf_get_u16bit(value_7, 1), true);     // bit 1 should be ocf_set

  uint16_t value_8 = 255;                  // Binary: 0000000011111111
  OCF_TEST_EQU(ocf_count_u16bit(value_8, true), 8);   // should have 8 ocf_set bits
  OCF_TEST_EQU(ocf_count_u16bit(value_8, false), 8);  // should have 8 unocf_set bits
  
  value_8 = ocf_set_u16bit(value_8, 15);
  OCF_TEST_EQU(ocf_get_u16bit(value_8, 15), true);    // MSB should be ocf_set
  OCF_TEST_EQU(ocf_count_u16bit(value_8, true), 9);   // should have 9 ocf_set bits

  uint16_t value_9 = 1024;                 // Binary: 0000010000000000, bit 10 is ocf_set
  OCF_TEST_EQU(ocf_get_u16bit(value_9, 10), true);    // bit 10 should be 1
  OCF_TEST_EQU(ocf_get_u16bit(value_9, 0), false);    // bit 0 should be 0
  
  value_9 = ocf_xchg_u16bit(value_9, 10, 0);   // exchange bits 10 and 0
  OCF_TEST_EQU(ocf_get_u16bit(value_9, 0), true);     // bit 0 should be 1
  OCF_TEST_EQU(ocf_get_u16bit(value_9, 10), false);   // bit 10 should be 0

  // ==================== 16-BIT SIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_16bit, ocf_set_16bit, ocf_reset_16bit, ocf_toggle_16bit, ocf_xchg_16bit, ocf_count_16bit
  
  int16_t value_10 = 256;                  // Binary: 0000000100000000, bit 8 is ocf_set
  OCF_TEST_EQU(ocf_get_16bit(value_10, 8), true);     // bit 8 should be 1
  OCF_TEST_EQU(ocf_get_16bit(value_10, 9), false);    // bit 9 should be 0
  
  value_10 = ocf_set_16bit(value_10, 9);
  OCF_TEST_EQU(ocf_get_16bit(value_10, 9), true);     // bit 9 should be ocf_set
  
  value_10 = ocf_toggle_16bit(value_10, 8);
  OCF_TEST_EQU(ocf_get_16bit(value_10, 8), false);    // bit 8 should be ocf_toggled to 0
  OCF_TEST_EQU(ocf_count_16bit(value_10, true), 1);   // should have 1 ocf_set bit

  // ==================== 32-BIT UNSIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_u32bit, ocf_set_u32bit, ocf_reset_u32bit, ocf_toggle_u32bit, ocf_xchg_u32bit, ocf_count_u32bit
  
  uint32_t value_11 = 65536;               // Binary: bit 16 is ocf_set
  OCF_TEST_EQU(ocf_get_u32bit(value_11, 16), true);   // bit 16 should be 1
  OCF_TEST_EQU(ocf_get_u32bit(value_11, 0), false);   // bit 0 should be 0
  
  value_11 = ocf_set_u32bit(value_11, 0);
  OCF_TEST_EQU(ocf_get_u32bit(value_11, 0), true);    // bit 0 should be ocf_set
  
  value_11 = ocf_reset_u32bit(value_11, 16);
  OCF_TEST_EQU(ocf_get_u32bit(value_11, 16), false);  // bit 16 should be cleared
  OCF_TEST_EQU(ocf_count_u32bit(value_11, true), 1);  // should have 1 ocf_set bit

  uint32_t value_12 = 0xFFFF;              // All lower 16 bits ocf_set
  OCF_TEST_EQU(ocf_count_u32bit(value_12, true), 16); // should have 16 ocf_set bits
  
  value_12 = ocf_toggle_u32bit(value_12, 31);  // ocf_toggle MSB
  OCF_TEST_EQU(ocf_get_u32bit(value_12, 31), true);   // MSB should be ocf_set
  OCF_TEST_EQU(ocf_count_u32bit(value_12, true), 17); // should have 17 ocf_set bits

  uint32_t value_13 = 0x80000000;          // Only MSB is ocf_set
  OCF_TEST_EQU(ocf_get_u32bit(value_13, 31), true);   // bit 31 should be 1
  
  value_13 = ocf_xchg_u32bit(value_13, 31, 0); // exchange MSB and LSB
  OCF_TEST_EQU(ocf_get_u32bit(value_13, 0), true);    // bit 0 should be 1
  OCF_TEST_EQU(ocf_get_u32bit(value_13, 31), false);  // bit 31 should be 0

  // ==================== 32-BIT SIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_32bit, ocf_set_32bit, ocf_reset_32bit, ocf_toggle_32bit, ocf_xchg_32bit, ocf_count_32bit
  
  int32_t value_14 = 1000;
  OCF_TEST_EQU(ocf_get_32bit(value_14, 9), true);     // Check bit 9
  OCF_TEST_EQU(ocf_get_32bit(value_14, 31), false);   // Sign bit should be 0 for positive
  
  value_14 = ocf_set_32bit(value_14, 15);
  OCF_TEST_EQU(ocf_get_32bit(value_14, 15), true);    // bit 15 should be ocf_set
  
  int32_t value_15 = -1;                   // All bits ocf_set in two's complement
  OCF_TEST_EQU(ocf_count_32bit(value_15, true), 32);  // all 32 bits should be ocf_set
  OCF_TEST_EQU(ocf_count_32bit(value_15, false), 0);  // no bits should be unocf_set

  // ==================== 64-BIT UNSIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_u64bit, ocf_set_u64bit, ocf_reset_u64bit, ocf_toggle_u64bit, ocf_xchg_u64bit, ocf_count_u64bit
  
  uint64_t value_16 = 0x0000000100000000ULL; // Bit 32 is ocf_set
  OCF_TEST_EQU(ocf_get_u64bit(value_16, 32), true);   // bit 32 should be 1
  OCF_TEST_EQU(ocf_get_u64bit(value_16, 0), false);   // bit 0 should be 0
  
  value_16 = ocf_set_u64bit(value_16, 0);
  OCF_TEST_EQU(ocf_get_u64bit(value_16, 0), true);    // bit 0 should be ocf_set
  
  value_16 = ocf_reset_u64bit(value_16, 32);
  OCF_TEST_EQU(ocf_get_u64bit(value_16, 32), false);  // bit 32 should be cleared
  OCF_TEST_EQU(ocf_count_u64bit(value_16, true), 1);  // should have 1 ocf_set bit

  uint64_t value_17 = 0xFFFFFFFFFFFFFFFFULL; // All bits ocf_set
  OCF_TEST_EQU(ocf_count_u64bit(value_17, true), 64); // should have 64 ocf_set bits
  
  value_17 = ocf_toggle_u64bit(value_17, 0);
  OCF_TEST_EQU(ocf_get_u64bit(value_17, 0), false);   // bit 0 should be ocf_toggled to 0
  OCF_TEST_EQU(ocf_count_u64bit(value_17, true), 63); // should have 63 ocf_set bits

  uint64_t value_18 = 0x8000000000000000ULL; // Only MSB (bit 63) is ocf_set
  OCF_TEST_EQU(ocf_get_u64bit(value_18, 63), true);   // bit 63 should be 1
  
  value_18 = ocf_xchg_u64bit(value_18, 63, 0); // exchange bits 63 and 0
  OCF_TEST_EQU(ocf_get_u64bit(value_18, 0), true);    // bit 0 should be 1
  OCF_TEST_EQU(ocf_get_u64bit(value_18, 63), false);  // bit 63 should be 0

  // ==================== 64-BIT SIGNED INTEGER OCF_TESTS ====================
  // OCF_TESTing: ocf_get_64bit, ocf_set_64bit, ocf_reset_64bit, ocf_toggle_64bit, ocf_xchg_64bit, ocf_count_64bit
  
  int64_t value_19 = 1000000;
  OCF_TEST_EQU(ocf_count_64bit(value_19, true), 7);   // should have 7 ocf_set bits
  
  value_19 = ocf_set_64bit(value_19, 62);
  OCF_TEST_EQU(ocf_get_64bit(value_19, 62), true);    // bit 62 should be ocf_set
  
  int64_t value_20 = -256;                 // Two's complement representation
  OCF_TEST_EQU(ocf_get_64bit(value_20, 8), false);    // bit 8 should be 0
  
  value_20 = ocf_toggle_64bit(value_20, 32);
  OCF_TEST_EQU(ocf_get_64bit(value_20, 32), true);    // bit 32 should be ocf_toggled

  // generic OCF_TESTs for ocf_get_bit, ocf_set_bit, ocf_reset_bit, ocf_toggle_bit, ocf_xchg_bit using all values before

  OCF_TEST_EQU(ocf_get_bit(value_1, 3), true);    // bit 3 should still be 1
  OCF_TEST_EQU(ocf_get_bit(value_1, 2), false);   // bit 2 should be 0
  value_1 = ocf_set_bit(value_1, 2); // value_1: 1000-1101
  OCF_TEST_EQU(ocf_get_bit(value_1, 2), true); // bit 2 should now be 1
  value_1 = ocf_reset_bit(value_1, 3); // value_1: 1000-0101
  OCF_TEST_EQU(ocf_get_bit(value_1, 3), false); // bit 3 should now be 0
  value_1 = ocf_toggle_bit(value_1, 0); // value_1: 1000-0100
  OCF_TEST_EQU(ocf_get_bit(value_1, 0), false); // bit 0 should now be 0
  value_1 = ocf_xchg_bit(value_1, 7, 0); // value_1: 0000-0100
  OCF_TEST_EQU(ocf_get_bit(value_1, 7), false); // bit 7 should now be 0
  OCF_TEST_EQU(ocf_get_bit(value_1, 0), false); // bit 0 should still be 0
  OCF_TEST_EQU(ocf_count_bit(value_1, true), 1); // value_1 should have 1 ocf_set bit
  OCF_TEST_EQU(ocf_count_bit(value_1, false), 7); // value_1 should have 7 unocf_set bits

OCF_TEST_EXIT(true)