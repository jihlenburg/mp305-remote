/* Address: ram:0005b5e4; name: FUN_ram_0005b5e4; body bytes: 296 */

bool FUN_ram_0005b5e4(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  gp = 0x20004000;
  iVar2 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 0x17;
  if (iVar2 != 0) {
    *(undefined1 *)(iVar2 + 2) = 3;
    uStack_28 = tmos_rand();
    uStack_24 = tmos_rand();
    tmos_memcpy(param_1 + 0x199,&uStack_28,8);
    *(uint *)(param_1 + 200) =
         (uint)*(byte *)(param_1 + 0x19b) * 0x100 + (uint)*(byte *)(param_1 + 0x19a) * 0x10000 +
         (uint)*(byte *)(param_1 + 0x19c) + (uint)*(byte *)(param_1 + 0x199) * 0x1000000;
    *(uint *)(param_1 + 0xc4) =
         (uint)*(byte *)(param_1 + 0x19f) * 0x100 + (uint)*(byte *)(param_1 + 0x19e) * 0x10000 +
         (uint)*(byte *)(param_1 + 0x1a0) + (uint)*(byte *)(param_1 + 0x19d) * 0x1000000;
    uStack_28 = tmos_rand();
    tmos_memcpy(param_1 + 0x1a1,&uStack_28,4);
    *(uint *)(param_1 + 0xdc) =
         (uint)*(byte *)(param_1 + 0x1a2) * 0x100 + (uint)*(byte *)(param_1 + 0x1a3) * 0x10000 +
         (uint)*(byte *)(param_1 + 0x1a1) + (uint)*(byte *)(param_1 + 0x1a4) * 0x1000000;
    tmos_memcpy(iVar2 + 3,param_1 + 399,8);
    uVar1 = *(undefined1 *)(param_1 + 0x198);
    *(undefined1 *)(iVar2 + 0xb) = *(undefined1 *)(param_1 + 0x197);
    *(undefined1 *)(iVar2 + 0xc) = uVar1;
    tmos_memcpy(iVar2 + 0xd,param_1 + 0x199,8);
    tmos_memcpy(iVar2 + 0x15,param_1 + 0x1a1,4);
    *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
    *(undefined1 *)(param_1 + 0x10) = 0x20;
  }
  return iVar2 == 0;
}

