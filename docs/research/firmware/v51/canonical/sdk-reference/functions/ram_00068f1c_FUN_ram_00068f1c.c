/* Address: ram:00068f1c; name: FUN_ram_00068f1c; body bytes: 366 */

void FUN_ram_00068f1c(undefined2 param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  undefined2 local_30 [2];
  undefined1 uStack_2c;
  undefined1 uStack_2b;
  undefined1 auStack_2a [16];
  byte bStack_1a;
  ushort uStack_18;
  undefined1 uStack_14;
  
  gp = 0x20004000;
  tmos_memset(local_30,0,0x20);
  uStack_14 = DAT_ram_200019c9;
  local_30[0] = param_1;
  if (param_3 == 0) {
    uStack_2c = DAT_ram_20001a91;
    uStack_2b = DAT_ram_20001a93;
    uVar2 = (ushort)DAT_ram_20001a92;
    uStack_18 = uStack_18 & 0xf8f8 | uVar2 & 1 | uVar2 & 2 | uVar2 & 4 | (uVar2 & 0x10) << 4 |
                (uVar2 & 0x20) << 4 | (uVar2 & 0x40) << 4;
    tmos_memcpy(auStack_2a,&DAT_ram_20001b14,0x10);
    bVar1 = DAT_ram_20001a90;
  }
  else {
    uStack_2c = DAT_ram_20001a99;
    uStack_2b = DAT_ram_20001a9b;
    uVar2 = (ushort)DAT_ram_20001a9a;
    uStack_18 = uStack_18 & 0xf8f8 | uVar2 & 1 | uVar2 & 2 | uVar2 & 4 | (uVar2 & 0x10) << 4 |
                (uVar2 & 0x20) << 4 | (uVar2 & 0x40) << 4;
    tmos_memcpy(auStack_2a,&DAT_ram_20001b24,0x10);
    bVar1 = DAT_ram_20001a98;
  }
  if (((bVar1 & 1) != 0) && (param_2 != 0)) {
    uStack_18 = uStack_18 | 2;
  }
  bStack_1a = bVar1 | bStack_1a;
  FUN_ram_00044ac6(local_30,param_3);
  return;
}

