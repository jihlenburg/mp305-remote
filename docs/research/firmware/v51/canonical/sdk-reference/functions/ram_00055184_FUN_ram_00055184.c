/* Address: ram:00055184; name: FUN_ram_00055184; body bytes: 1146 */

void FUN_ram_00055184(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  undefined1 uVar6;
  int iVar7;
  undefined1 uStack_2c;
  undefined1 uStack_2b;
  undefined1 auStack_2a [6];
  undefined1 uStack_24;
  
  iVar2 = DAT_ram_20001dc0;
  gp = 0x20004000;
  iVar7 = DAT_ram_20001dc0 + 0x14;
LAB_ram_000551c4:
  switch(*(char *)(iVar2 + 0xb) + 'n') {
  case '\0':
    if ((DAT_ram_20001e96 & 1) == 0) goto LAB_ram_0005525a;
    DAT_ram_20001e96 = 0;
    if ((1 < *(byte *)(iVar2 + 0x10)) && (*(byte *)(iVar2 + 0x10) != 6)) goto LAB_ram_0005523c;
    uVar6 = 0x9b;
    goto LAB_ram_00055280;
  case '\x01':
    if ((DAT_ram_20001e96 & 1) == 0) goto LAB_ram_000555bc;
    DAT_ram_20001e96 = 0;
    goto LAB_ram_00055294;
  case '\x02':
    if ((DAT_ram_20001e96 & 1) == 0) goto LAB_ram_000555bc;
    DAT_ram_20001e96 = 0;
    FUN_ram_00062262();
    iVar3 = DAT_ram_20001eb0;
    if (((DAT_ram_20001dd4 == 2) || (DAT_ram_20001dd4 == 3)) &&
       (*(uint *)(DAT_ram_20001eb0 + 0x60) >> 1 < *(ushort *)(iVar2 + 0x72) + 300)) {
      *(undefined1 *)(iVar2 + 0xb) = 0x95;
      if (*(uint *)(iVar3 + 0x60) >> 1 == 0) goto LAB_ram_000553e8;
    }
    else {
      cVar5 = *(char *)(iVar2 + 0x19);
      cVar1 = *(char *)(iVar2 + 0x1a);
      if (cVar5 == '\0') {
        if ((cVar1 != '\0') && (*(char *)(iVar2 + 10) == '\0')) {
LAB_ram_0005543a:
          *(char *)(iVar2 + 10) = cVar1;
LAB_ram_0005540a:
          FUN_ram_0005480a(iVar2);
        }
      }
      else if (cVar5 == *(char *)(iVar2 + 10)) {
        if (cVar1 != '\0') goto LAB_ram_0005543a;
      }
      else if (*(char *)(iVar2 + 10) != cVar1) {
        *(char *)(iVar2 + 10) = cVar5;
        goto LAB_ram_0005540a;
      }
      if (DAT_ram_20001e9b == '\0') {
        if ((DAT_ram_20001dd4 != 2) && (DAT_ram_20001dd4 != 3)) goto LAB_ram_000553e8;
        uVar6 = 0x95;
        goto LAB_ram_00055280;
      }
    }
    goto LAB_ram_000551c4;
  case '\x03':
    do {
    } while (DAT_ram_20001dd4 != 4);
    FUN_ram_00053ed0(iVar2);
    goto LAB_ram_000551c4;
  case '\x04':
    if ((DAT_ram_20001e96 & 1) == 0) goto LAB_ram_000555bc;
    DAT_ram_20001e96 = 0;
    if ((DAT_ram_20001dd4 & 0x10) != 0) {
      FUN_ram_00062262();
      do {
      } while ((DAT_ram_20001dd4 & 0x20) == 0);
      goto LAB_ram_00055464;
    }
    if ((DAT_ram_20001dd5 & 1) != 0) goto LAB_ram_00055480;
    if ((DAT_ram_20001dd4 & 0xf) == 5) {
      uVar4 = FUN_ram_00055ed6();
      if (uVar4 < (DAT_ram_20001bd3 & 3)) goto LAB_ram_000554a4;
    }
    else if ((DAT_ram_20001dd4 & 0xf) == 6) goto LAB_ram_000554b6;
    break;
  case '\x05':
    if ((DAT_ram_20001e97 & 1) != 0) {
      FUN_ram_00062262();
      DAT_ram_20001e9e = 0;
      *(uint *)(DAT_ram_20001e88 + 100) = *(uint *)(DAT_ram_20001e88 + 100) & 0xfffffffb;
      DAT_ram_40001018 = (ushort)(((uint)DAT_ram_40001018 << 0x11) >> 0x11);
      goto LAB_ram_000553e8;
    }
    if (*(int *)(DAT_ram_20001eb0 + 100) != 0) goto LAB_ram_000551c4;
    FUN_ram_00062262();
    DAT_ram_20001e9e = 0;
    *(uint *)(DAT_ram_20001e88 + 100) = *(uint *)(DAT_ram_20001e88 + 100) & 0xfffffffb;
    DAT_ram_40001018 = (ushort)(((uint)DAT_ram_40001018 << 0x11) >> 0x11);
    DAT_ram_20001e98 = 0;
    goto LAB_ram_000553e8;
  case '\x06':
    if ((DAT_ram_20001e96 & 1) != 0) {
      DAT_ram_20001e96 = 0;
      if ((DAT_ram_20001dd4 & 0x10) == 0) {
        if ((DAT_ram_20001dd5 & 1) == 0) {
          if ((DAT_ram_20001dd4 & 0xf) == 5) {
LAB_ram_000554a4:
            uVar6 = 0x9d;
          }
          else {
            if ((DAT_ram_20001dd4 & 0xf) != 6) {
              FUN_ram_00062262();
              gp = 0x20004000;
              return;
            }
LAB_ram_000554b6:
            DAT_ram_20001e96 = 0;
            uVar6 = 0x9c;
          }
        }
        else {
LAB_ram_00055480:
          DAT_ram_20001e96 = 0;
          FUN_ram_00062262();
          uVar6 = 0x9e;
        }
LAB_ram_00055280:
        *(undefined1 *)(iVar2 + 0xb) = uVar6;
      }
      else {
        FUN_ram_00062262();
        do {
        } while ((DAT_ram_20001dd4 & 0x20) == 0);
LAB_ram_00055464:
        DAT_ram_20001dd4 = DAT_ram_20001dd4 & 0xcf;
        FUN_ram_00053cca(iVar2);
      }
    }
    goto LAB_ram_000551c4;
  case '\a':
    if ((DAT_ram_20001e96 & 1) != 0) {
      DAT_ram_20001e96 = 0;
      if ((DAT_ram_20001dd4 & 0x10) != 0) goto LAB_ram_0005559e;
      goto LAB_ram_00055298;
    }
LAB_ram_000555bc:
    if (*(int *)(DAT_ram_20001eb0 + 100) != 0) goto LAB_ram_000551c4;
LAB_ram_000555c6:
    DAT_ram_20001e98 = 0;
    break;
  case '\b':
    if ((DAT_ram_20001e96 & 1) != 0) {
      DAT_ram_20001e96 = 0;
      FUN_ram_00062262();
      FUN_ram_00053524(iVar2);
      FUN_ram_0005501c(iVar2);
      gp = 0x20004000;
      return;
    }
    DAT_ram_20001e98 = 0;
    break;
  case '\t':
    FUN_ram_00062030(0,0x25,0);
    FUN_ram_200011be(1,0,0x25);
    if ((DAT_ram_20001e97 & 1) == 0) {
LAB_ram_0005525a:
      DAT_ram_20001e98 = 0;
LAB_ram_0005523c:
      FUN_ram_00062262();
      FUN_ram_00053894(iVar2);
      gp = 0x20004000;
      return;
    }
    DAT_ram_20001e97 = 0;
    iVar3 = FUN_ram_20001120(*(undefined4 *)(iVar2 + 0x50),0,iVar7,0);
    if (iVar3 == 0) {
      FUN_ram_00055078(iVar2);
    }
    if (*(char *)(iVar2 + 0xb) != -0x6d) goto LAB_ram_0005523c;
    goto LAB_ram_000551c4;
  case '\n':
    FUN_ram_00062030(*(undefined1 *)(iVar2 + 99),0x25,0);
    FUN_ram_200011be(1,*(undefined1 *)(iVar2 + 99),0x25);
    if ((DAT_ram_20001e97 & 1) == 0) goto LAB_ram_000555c6;
    DAT_ram_20001e97 = 0;
    iVar3 = FUN_ram_20001120(*(undefined4 *)(iVar2 + 0x50),0,iVar7,0);
    if (iVar3 == 0) {
      FUN_ram_000538d8(iVar2);
    }
    cVar1 = *(char *)(iVar2 + 0xb);
    cVar5 = -0x67;
LAB_ram_00055344:
    if (cVar1 == cVar5) goto LAB_ram_000551c4;
    break;
  case '\v':
    FUN_ram_00062030(*(undefined1 *)(iVar2 + 99),0x25,0);
    FUN_ram_200011be(1,*(undefined1 *)(iVar2 + 99),0x25);
    if ((DAT_ram_20001e97 & 1) != 0) {
      DAT_ram_20001e97 = 0;
      iVar3 = FUN_ram_20001120(*(undefined4 *)(iVar2 + 0x50),0,iVar7,0);
      if (iVar3 == 0) {
        FUN_ram_00053b6e(iVar2);
      }
      cVar1 = *(char *)(iVar2 + 0xb);
      cVar5 = -0x66;
      goto LAB_ram_00055344;
    }
    goto LAB_ram_000555c6;
  case '\f':
    goto switchD_ram_000551dc_caseD_c;
  }
  FUN_ram_00062262();
LAB_ram_000553e8:
  FUN_ram_00053848(iVar2);
  gp = 0x20004000;
  return;
switchD_ram_000551dc_caseD_c:
  *(undefined1 *)(iVar2 + 0x7c) = 2;
  FUN_ram_0005322c(iVar2);
  if (*(char *)(iVar2 + 0xb) != -0x69) {
    gp = 0x20004000;
    return;
  }
  goto LAB_ram_000551c4;
LAB_ram_0005559e:
  do {
  } while ((DAT_ram_20001dd4 & 0x20) == 0);
  FUN_ram_00053cca(iVar2);
  DAT_ram_20001dd4 = DAT_ram_20001dd4 & 0xcf;
LAB_ram_00055294:
  FUN_ram_00062262();
LAB_ram_00055298:
  FUN_ram_00053848(iVar2);
  if ((DAT_ram_20001a78 != 0) && (*(int *)(DAT_ram_20001a78 + 4) != 0)) {
    uStack_2c = 2;
    uStack_2b = *(undefined1 *)(iVar2 + 0x45);
    uStack_24 = *(undefined1 *)(iVar2 + 0x14);
    tmos_memcpy(auStack_2a,iVar2 + 0x46,6);
    (**(code **)(DAT_ram_20001a78 + 4))(&uStack_2c);
  }
  if (*(char *)(iVar2 + 0x67) != '\0') {
    thunk_FUN_ram_00051ffa(*(undefined1 *)(iVar2 + 8),*(undefined1 *)(iVar2 + 0x45),iVar2 + 0x46);
  }
  return;
}

