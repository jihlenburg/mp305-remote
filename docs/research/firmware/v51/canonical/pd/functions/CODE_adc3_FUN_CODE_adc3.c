/* Address: CODE:adc3; name: FUN_CODE_adc3; body bytes: 36 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_adc3(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  byte bVar1;
  
  bVar1 = (byte)param_1;
  if (param_4 == '\x01') {
    FUN_CODE_ad92((char)((ushort)param_1 >> 8) + (param_3 - ((CARRY1(bVar1,param_2) << 7) >> 7)),
                  bVar1 + param_2);
    return;
  }
  if (param_4 == '\0') {
    FUN_CODE_ad79(param_2 + bVar1);
    return;
  }
  if (param_4 == -2) {
    FUN_CODE_af51(param_2 + bVar1);
    return;
  }
  return;
}

