/* Address: ram:00059856; name: FUN_ram_00059856; body bytes: 304 */

void FUN_ram_00059856(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  uint uStack_18;
  uint uStack_14;
  
  gp = 0x20004000;
  iVar2 = (uint)(*(byte *)(param_1 + 0x136) >> 3) + param_1;
  bVar1 = *(byte *)(iVar2 + 0x130);
  uVar3 = *(byte *)(param_1 + 0x136) & 7;
  if (((int)(uint)bVar1 >> uVar3 & 1U) == 0) {
    *(byte *)(iVar2 + 0x130) = (byte)(1 << uVar3) | bVar1;
    return;
  }
  if (((*(byte *)(param_1 + 0x11) & 2) != 0) || ((*(uint *)(param_1 + 0xa4) & 2) != 0)) {
    return;
  }
  uVar3 = FUN_ram_000582da(param_1 + 0x138);
  if (*(byte *)(param_1 + 0x135) < uVar3) {
    iVar2 = FUN_ram_00061e3a((int)((*(byte *)(param_1 + 0x32) - 0xc) * 0x1000000) >> 0x18,
                             *(undefined1 *)(param_1 + 0x136));
    if (iVar2 != 0) goto LAB_ram_000598e4;
    uVar4 = FUN_ram_0006bab6(1,0,*(undefined1 *)(param_1 + 0x136));
    uStack_18 = *(uint *)(param_1 + 0x138) & ~(uint)uVar4;
    uStack_14 = *(uint *)(param_1 + 0x13c) & ~(uint)((ulonglong)uVar4 >> 0x20);
  }
  else {
    uStack_18 = 0xffffffff;
    uStack_14 = 0x1f;
    FUN_ram_200012e0((int)((*(byte *)(param_1 + 0x32) - 10) * 0x1000000) >> 0x18,&uStack_18);
    if ((*(uint *)(param_1 + 0x138) == (uStack_18 & *(uint *)(param_1 + 0x138))) &&
       (*(uint *)(param_1 + 0x13c) == (uStack_14 & *(uint *)(param_1 + 0x13c))))
    goto LAB_ram_000598e4;
    uVar3 = FUN_ram_000582da(&uStack_18);
    if (uVar3 < 10) {
      *(char *)(param_1 + 0x135) = (char)uVar3;
      goto LAB_ram_000598e4;
    }
    *(char *)(param_1 + 0x135) = (char)uVar3 + -5;
  }
  tmos_memcpy(param_1 + 0x128,&uStack_18,5);
  *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 2;
LAB_ram_000598e4:
  if (((*(char *)(param_1 + 0x174) == '\0') &&
      (uVar3 = FUN_ram_0006ba8a(uStack_18,uStack_14,*(undefined1 *)(param_1 + 0x136)),
      (uVar3 & 1) != 0)) && ((*(uint *)(param_1 + 0x10c) & 0x80) != 0)) {
    *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x400000;
  }
  return;
}

