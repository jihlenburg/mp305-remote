/* Address: ram:000502da; name: FUN_ram_000502da; body bytes: 98 */

undefined4 FUN_ram_000502da(undefined2 *param_1)

{
  undefined4 uVar1;
  undefined1 auStack_50 [72];
  
  gp = 0x20004000;
  if (DAT_ram_20001f04 != (undefined4 *)0x0) {
    uVar1 = 0xfe;
    if ((code *)*DAT_ram_20001f04 != (code *)0x0) {
      (*(code *)*DAT_ram_20001f04)(*(int *)(param_1 + 0x40) + 0x80,*(int *)(param_1 + 0x40) + 0xc0);
      tmos_memcpy(auStack_50,*(int *)(param_1 + 0x40) + 0x80,0x40);
      uVar1 = FUN_ram_0004e78a(*param_1,0x41,auStack_50,&LAB_ram_0005017c);
    }
    return uVar1;
  }
  return 0xfe;
}

