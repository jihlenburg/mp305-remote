/* Address: 0001bc68; name: FUN_0001bc68; body bytes: 24 */

undefined4 FUN_0001bc68(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_00015ee8();
  if ((-1 < (int)((uint)(byte)pcVar1[6] << 0x18)) && (*pcVar1 != '\0')) {
    return 1;
  }
  return 0;
}

