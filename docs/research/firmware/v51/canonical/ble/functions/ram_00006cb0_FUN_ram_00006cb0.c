/* Address: ram:00006cb0; name: FUN_ram_00006cb0; body bytes: 700 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_ram_00006cb0(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  undefined1 auStack_20 [16];
  
  gp = &DAT_ram_20002000;
  if ((short)param_2 < 0) {
    iVar2 = (*_DAT_ram_0004006c)(DAT_ram_20002f44);
    if (iVar2 != 0) {
      (*_DAT_ram_00040068)();
    }
    gp = &DAT_ram_20002000;
    return param_2 ^ 0x8000;
  }
  if ((param_2 & 1) != 0) {
    (*_DAT_ram_000401a4)
              (DAT_ram_20002f44,&DAT_ram_20005140,&PTR_FUN_ram_00007106_ram_20002e6c,param_4,param_5
               ,_DAT_ram_000401a4);
    (*_DAT_ram_00040058)(DAT_ram_20002f44,0x800,2);
    (*_DAT_ram_00040058)(DAT_ram_20002f44,0x100,0x10);
    (*_DAT_ram_00040058)(DAT_ram_20002f44,2,0x640);
    gp = &DAT_ram_20002000;
    return param_2 ^ 1;
  }
  if ((param_2 & 2) == 0) {
    if ((param_2 & 0x800) != 0) {
      FUN_ram_00004bb8();
      (*_DAT_ram_00040058)(DAT_ram_20002f44,0x800,2);
      gp = &DAT_ram_20002000;
      return (param_2 ^ 0x800) & 0xffff;
    }
    if ((param_2 & 0x100) != 0) {
      DAT_ram_40001043 = 0;
      (*_DAT_ram_00040058)(DAT_ram_20002f44,0x100,0x10,param_4,param_5,_DAT_ram_00040058);
      gp = &DAT_ram_20002000;
      return param_2 ^ 0x100;
    }
    if ((param_2 & 0x400) != 0) {
      if (DAT_ram_20002fb5 == '\0') {
        (*_DAT_ram_00040058)(DAT_ram_20002f44,0x400,0x140,param_4,param_5,_DAT_ram_00040058);
      }
      gp = &DAT_ram_20002000;
      return param_2 ^ 0x400;
    }
    if ((param_2 & 8) == 0) {
      gp = &DAT_ram_20002000;
      return 0;
    }
    (*_DAT_ram_000401a8)(DAT_ram_20002ffc,6,0x28,0,500,DAT_ram_20002f44,_DAT_ram_000401a8);
    gp = &DAT_ram_20002000;
    return param_2 ^ 8;
  }
  iVar2 = FUN_ram_000047fe();
  if ((iVar2 == 0) || (cVar3 = '3', DAT_ram_20002e9c == '3')) {
    iVar2 = FUN_ram_000047fe();
    bVar1 = false;
    if ((iVar2 == 0) && (cVar3 = '0', DAT_ram_20002e9c != '0')) goto LAB_ram_00006d70;
  }
  else {
LAB_ram_00006d70:
    DAT_ram_20002e9c = cVar3;
    bVar1 = true;
  }
  cVar3 = ' ';
  if ((DAT_ram_20002f8a != '\0') && (DAT_ram_20002f89 != '\x02')) {
    cVar3 = 'S';
  }
  if (DAT_ram_20002ea6 != cVar3) {
    bVar1 = true;
    DAT_ram_20002ea6 = cVar3;
  }
  (*_DAT_ram_00040048)(auStack_20,0xff,0xe);
  FUN_ram_200028d6(0xb,0x6e00,&DAT_ram_200042b0,0x16);
  iVar2 = (*_DAT_ram_0004003c)(auStack_20,&DAT_ram_200042be,8);
  if (iVar2 == 0) {
    (*_DAT_ram_0004004c)(s_MP305B_ram_20002e9e,&DAT_ram_200042be,8);
  }
  else if (!bVar1) goto LAB_ram_00006e3e;
  (*_DAT_ram_00040174)(0x307,0x1f,&DAT_ram_20002e98);
LAB_ram_00006e3e:
  if ((DAT_ram_20002ff8 == 4) &&
     (((DAT_ram_20002ff0 = DAT_ram_20002ff0 + 0x640, DAT_ram_20002ff4 == 0 ||
       (DAT_ram_20002ff4 == 1)) && (47999 < DAT_ram_20002ff0)))) {
    (*_DAT_ram_0004017c)(DAT_ram_20002ffc);
  }
  (*_DAT_ram_00040058)(DAT_ram_20002f44,2,0x640);
  return param_2 ^ 2;
}

