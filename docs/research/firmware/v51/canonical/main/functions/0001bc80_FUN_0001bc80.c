/* Address: 0001bc80; name: FUN_0001bc80; body bytes: 24 */

undefined4 FUN_0001bc80(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_00015ee8();
  if (((int)((uint)(byte)pcVar1[6] << 0x18) < 0) && (*pcVar1 != '\0')) {
    return 1;
  }
  return 0;
}

