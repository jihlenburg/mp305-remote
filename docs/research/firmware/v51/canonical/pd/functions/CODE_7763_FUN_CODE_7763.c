/* Address: CODE:7763; name: FUN_CODE_7763; body bytes: 81 */

undefined1 FUN_CODE_7763(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_04ab = 0;
  DAT_EXTMEM_04ac = 0;
  uVar1 = (&DAT_CODE_b9c2)[(byte)((char)((ushort)DAT_INTMEM_b3 * 6) + param_2)];
  DAT_EXTMEM_04a9 = param_2;
  DAT_EXTMEM_04aa = uVar1;
  if (_1_4 == '\0') {
    _1_5 = 1;
    FUN_CODE_94ae((char)((ushort)DAT_INTMEM_b3 * 6 >> 8));
  }
  else {
    FUN_CODE_91be();
  }
  DAT_EXTMEM_04ab = param_1;
  DAT_EXTMEM_04ac = uVar1;
  FUN_CODE_9b8f(param_1,uVar1,DAT_EXTMEM_04a9);
  return DAT_EXTMEM_04ac;
}

