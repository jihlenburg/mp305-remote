/* Address: ram:200014ae; name: FUN_ram_200014ae; body bytes: 476 */

void FUN_ram_200014ae(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_ram_20001eb0;
  gp = 0x20004000;
  if ((*(int *)(DAT_ram_20001eb0 + 0xc) << 0x11 < 0) && (*(int *)(DAT_ram_20001eb0 + 8) << 0x11 < 0)
     ) {
    *(undefined4 *)(DAT_ram_20001eb0 + 0x68) = 0xffffffff;
    DAT_ram_20001b80 = DAT_ram_20001b80 + 1;
    *(undefined4 *)(iVar2 + 8) = 0x4000;
  }
  if ((*(uint *)(iVar2 + 8) >> 3 & 1) != 0) {
    DAT_ram_20001e96 = DAT_ram_20001e96 | 1;
    DAT_ram_20001e98 = -0x80;
    *(undefined4 *)(iVar2 + 8) = 8;
  }
  if ((*(uint *)(iVar2 + 8) & 1) != 0) {
    DAT_ram_20001e95 = DAT_ram_20001e95 | 1;
    *(undefined4 *)(iVar2 + 8) = 1;
  }
  if (((*(uint *)(iVar2 + 8) >> 2 & 1) == 0) && ((*(uint *)(iVar2 + 8) >> 1 & 1) == 0))
  goto LAB_ram_2000158c;
  if ((*(uint *)(iVar2 + 8) >> 2 & 1) == 0) {
    DAT_ram_20001e97 = DAT_ram_20001e97 | 1;
    uVar3 = 2;
  }
  else {
    if ((*DAT_ram_20001e88 >> 0xc & 3) == 0) {
      cVar1 = *(char *)(DAT_ram_20001eac + 1);
      if ((*(uint *)(iVar2 + 0x50) & 0x20) == 0) {
        if (cVar1 == '\0') goto LAB_ram_20001568;
        if (cVar1 == '\x01') {
          uVar3 = 0x6b;
        }
        else if (cVar1 == '\x02') {
          uVar3 = 0x6f;
        }
        else {
          if (cVar1 != '\x03') goto LAB_ram_20001638;
          uVar3 = 0x73;
        }
      }
      else if (cVar1 == '\0') {
LAB_ram_20001568:
        uVar3 = 0x67;
      }
      else {
LAB_ram_20001638:
        uVar3 = 0x75;
      }
    }
    else {
      uVar3 = 0x76;
    }
    *(undefined4 *)(iVar2 + 0x1c) = uVar3;
    DAT_ram_20001e94 = DAT_ram_20001e94 | 1;
    uVar3 = 4;
  }
  *(undefined4 *)(iVar2 + 8) = uVar3;
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
LAB_ram_2000158c:
  iVar2 = DAT_ram_20001eb0;
  if (*(int *)(DAT_ram_20001eb0 + 8) << 0x13 < 0) {
    if ((DAT_ram_20001dd4 & 0x10) == 0) {
      if (((DAT_ram_20001dd4 & 0xf) == 2) || ((DAT_ram_20001dd4 & 0xf) == 3)) {
        DAT_ram_20001dd4 = 4;
      }
    }
    else {
      DAT_ram_20001dd4 = DAT_ram_20001dd4 | 0x20;
    }
    *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x1000;
  }
  if (*(int *)(iVar2 + 8) << 0x12 < 0) {
    if (DAT_ram_20001e98 < '\0') {
      DAT_ram_20001e98 = '\x01';
    }
    *(undefined4 *)(iVar2 + 8) = 0x2000;
  }
  if (*(int *)(iVar2 + 8) << 0x10 < 0) {
    if ((DAT_ram_20001dd5 & 1) == 0) {
      if ((DAT_ram_20001dd5 & 4) != 0) {
        DAT_ram_20001dd5 = DAT_ram_20001dd5 | 8;
      }
    }
    else {
      DAT_ram_20001dd5 = DAT_ram_20001dd5 | 2;
    }
    *(undefined4 *)(iVar2 + 8) = 0x8000;
  }
  return;
}

