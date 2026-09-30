/* Address: ram:000555fe; name: FUN_ram_000555fe; body bytes: 584 */

void FUN_ram_000555fe(void)

{
  ushort uVar1;
  int iVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  
  iVar2 = DAT_ram_20001db4;
  gp = 0x20004000;
  if (DAT_ram_20001db4 == 0) {
    gp = 0x20004000;
    return;
  }
  if (*(char *)(DAT_ram_20001db4 + 0xc) != '\x01') {
    gp = 0x20004000;
    return;
  }
  if (*(ushort *)(DAT_ram_20001db4 + 0x20) == 0) {
    uVar6 = 0xffffffff;
  }
  else {
    uVar6 = 0x640 / *(ushort *)(DAT_ram_20001db4 + 0x20);
  }
  DAT_ram_20001d60 = DAT_ram_20001d60 + 1;
  DAT_ram_20001dc0 = DAT_ram_20001db4;
  if ((int)uVar6 <= (int)(uint)DAT_ram_20001d60) {
    FUN_ram_00042954();
    DAT_ram_20001d60 = 0;
  }
  if ((*(char *)(iVar2 + 0xe) == '\a') && (*(byte *)(iVar2 + 0x69) != 0)) {
    uVar1 = *(ushort *)(iVar2 + 0x6e);
    if (*(byte *)(iVar2 + 0x69) <= uVar1) {
      *(undefined1 *)(iVar2 + 0x17) = 0x43;
      thunk_FUN_ram_00051fa2(0x43,*(undefined1 *)(iVar2 + 8),0,uVar1 & 0xff);
      FUN_ram_0005501c(iVar2);
      return;
    }
    *(ushort *)(iVar2 + 0x6e) = uVar1 + 1;
  }
  DAT_ram_20001dd4 = 1;
  uVar3 = FUN_ram_000428ec(1,0x23);
  *(undefined1 *)(iVar2 + 0x62) = uVar3;
  if (*(char *)(iVar2 + 0x18) != '\x03') {
    bVar7 = *(byte *)(iVar2 + 0xf);
    if (*(char *)(iVar2 + 0x18) == '\x02') {
      if ((bVar7 & 1) == 0) {
        *(undefined1 *)(iVar2 + 10) = 0x26;
LAB_ram_00055796:
        uVar3 = 0x27;
      }
      else {
        *(undefined1 *)(iVar2 + 10) = 0x25;
        if ((bVar7 & 2) == 0) goto LAB_ram_00055796;
        uVar3 = 0x26;
      }
      *(undefined1 *)(iVar2 + 0x19) = uVar3;
    }
    else if (bVar7 == 0) {
      if ((*(byte *)(iVar2 + 0x19) < 0x25) || (bVar7 = *(byte *)(iVar2 + 0x19) + 1, 0x27 < bVar7)) {
        bVar7 = 0x25;
      }
      *(byte *)(iVar2 + 0x19) = bVar7;
      *(undefined1 *)(iVar2 + 10) = *(undefined1 *)(iVar2 + 0x19);
    }
    else {
      if ((bVar7 & 1) == 0) {
        if ((bVar7 & 2) == 0) {
          uVar3 = 0x27;
        }
        else {
          uVar3 = 0x26;
        }
      }
      else {
        uVar3 = 0x25;
      }
      *(undefined1 *)(iVar2 + 10) = uVar3;
      *(undefined1 *)(iVar2 + 0x19) = 0;
    }
    *(undefined1 *)(iVar2 + 0x1a) = 0;
    goto LAB_ram_000556f0;
  }
  uVar6 = tmos_rand();
  if ((uVar6 & 3) == 0) {
    *(undefined1 *)(iVar2 + 10) = 0x27;
    uVar3 = 0x25;
LAB_ram_000556c8:
    *(undefined1 *)(iVar2 + 0x19) = uVar3;
    uVar3 = 0x26;
  }
  else {
    if ((uVar6 & 3) != 1) {
      *(undefined1 *)(iVar2 + 10) = 0x25;
      uVar3 = 0x27;
      goto LAB_ram_000556c8;
    }
    *(undefined1 *)(iVar2 + 10) = 0x26;
    *(undefined1 *)(iVar2 + 0x19) = 0x25;
    uVar3 = 0x27;
  }
  *(undefined1 *)(iVar2 + 0x1a) = uVar3;
LAB_ram_000556f0:
  uVar3 = DAT_ram_20001b67;
  if (*(char *)(iVar2 + 0xe) == '\x01') {
    uVar6 = (uint)*(ushort *)(iVar2 + 0x20);
  }
  else {
    iVar5 = FUN_ram_000428ec(1,0xe);
    uVar6 = (uint)*(ushort *)(iVar2 + 0x20) + iVar5;
  }
  tmos_start_task(uVar3,1,uVar6);
  if (((((*(byte *)(iVar2 + 0x35) & 2) == 0) || (*(char *)(iVar2 + 0x3c) == '\0')) ||
      (iVar5 = *(int *)(iVar2 + 0x30), iVar5 == 0)) || (*(char *)(iVar5 + 10) == '\0')) {
    *(undefined1 *)(iVar2 + 0x34) = 1;
  }
  else {
    *(undefined1 *)(iVar2 + 0x34) = 2;
    tmos_memcpy(iVar2 + 0x36,iVar5 + 0xc,6);
  }
  if (1 < *(byte *)(iVar2 + 0x7c)) {
    uVar6 = *(uint *)(iVar2 + 0x94);
    uVar4 = (*DAT_ram_20001c00)();
    if ((-1 < DAT_ram_20001bd2) && (uVar6 < uVar4)) {
      uVar6 = uVar6 + 0xa8c00000;
    }
    if (uVar6 - uVar4 < (uint)*(ushort *)(iVar2 + 0x74)) {
      return;
    }
  }
  FUN_ram_0005480a(iVar2);
  return;
}

