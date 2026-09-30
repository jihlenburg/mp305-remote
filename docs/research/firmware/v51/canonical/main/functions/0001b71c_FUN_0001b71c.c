/* Address: 0001b71c; name: FUN_0001b71c; body bytes: 36 */

undefined4 FUN_0001b71c(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *extraout_r2;
  undefined1 *puVar3;
  undefined8 uVar4;
  
  FUN_000144bc(100);
  enter_critical();
  FUN_000144a8(0);
  FUN_0001f23c(0);
  FUN_00015384(1,0x100);
  uVar4 = FUN_0001fc86();
  uVar1 = 0xfffffffd;
  if ((int)uVar4 != 0) {
    iVar2 = FUN_0001497c(0x100,(DAT_2003a60c >> ((DAT_40054020 & 0x7ffffff) >> 0x18)) / 20000);
    puVar3 = extraout_r2;
    if (iVar2 == 0) {
      for (; iVar2 = (int)((ulonglong)uVar4 >> 0x20), iVar2 != 0;
          uVar4 = CONCAT44(iVar2 + -1,(undefined1 *)uVar4 + 1)) {
        *(undefined1 *)uVar4 = *puVar3;
        puVar3 = puVar3 + 1;
      }
      return 0;
    }
    uVar1 = 0xfffffffb;
  }
  return uVar1;
}

