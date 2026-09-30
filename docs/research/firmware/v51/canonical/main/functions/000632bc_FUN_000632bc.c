/* Address: 000632bc; name: FUN_000632bc; body bytes: 16 */

int FUN_000632bc(uint param_1)

{
  return 0x1f - LZCOUNT(param_1 & ~param_1 + 1);
}

