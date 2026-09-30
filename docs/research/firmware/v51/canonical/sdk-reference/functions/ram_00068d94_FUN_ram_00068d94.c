/* Address: ram:00068d94; name: FUN_ram_00068d94; body bytes: 40 */

void FUN_ram_00068d94(void)

{
  uint uVar1;
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  uVar1 = FUN_ram_00068a86();
  auStack_11[0] = 10;
  if (1 < uVar1) {
    auStack_11[0] = 2;
  }
  GGS_SetParameter(5,1,auStack_11);
  return;
}

