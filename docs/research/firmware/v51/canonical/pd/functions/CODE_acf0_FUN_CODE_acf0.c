/* Address: CODE:acf0; name: FUN_CODE_acf0; body bytes: 19 */

/* Inferred entry from 7 raw LCALL encodings. Review control flow before relying on semantics. */

byte FUN_CODE_acf0(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  for (bVar3 = param_1; bVar3 != 0; bVar3 = bVar3 - 1) {
    bVar1 = param_5 >> 7;
    bVar2 = param_4 >> 7;
    param_1 = param_2 << 1 | param_3 >> 7;
    param_5 = param_5 << 1;
    param_4 = param_4 << 1 | bVar1;
    param_3 = param_3 << 1 | bVar2;
    param_2 = param_1;
  }
  return param_1;
}

