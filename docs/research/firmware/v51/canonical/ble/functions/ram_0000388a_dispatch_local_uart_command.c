/* Address: ram:0000388a; name: dispatch_local_uart_command; body bytes: 958 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Handles companion-local identity, advertising and update commands. */

void dispatch_local_uart_command(code *param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 uVar5;
  undefined1 auStack_140 [14];
  undefined1 auStack_132 [10];
  undefined1 auStack_128 [14];
  undefined1 auStack_11a [10];
  undefined1 auStack_110 [256];
  
  bVar1 = DAT_ram_200041a0;
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(auStack_110,0,0x100);
  if (bVar1 == 0x52) {
    if (DAT_ram_200041a1 == 'S') {
      DAT_ram_20002f8a = '\x01';
      if (DAT_ram_20003a48 == '\0') {
        FUN_ram_000055c0();
      }
      auStack_128[0] = 1;
    }
    else {
      DAT_ram_20002f8a = '\0';
      FUN_ram_0000566a();
      auStack_128[0] = 0;
    }
    (*_DAT_ram_00040174)(0x305,1,auStack_128);
    DAT_ram_20002f89 = '\0';
    uVar5 = 0x53;
LAB_ram_000038d0:
    _DAT_ram_2000409c = CONCAT22(_DAT_ram_2000409e,uVar5);
  }
  else {
    if (bVar1 < 0x53) {
      if (bVar1 == 0x10) {
        uVar4 = FUN_ram_00004be0();
        _DAT_ram_2000409c =
             CONCAT13((char)((uint)uVar4 >> 0x10),
                      CONCAT12((char)((uint)uVar4 >> 8),CONCAT11((char)uVar4,0x11)));
        DAT_ram_200040a0 = CONCAT31(DAT_ram_200040a0._1_3_,(char)((uint)uVar4 >> 0x18));
        DAT_ram_2000409a = 5;
        goto LAB_ram_00003a34;
      }
      if (bVar1 != 0x50) {
        if (bVar1 != 0) {
          gp = &DAT_ram_20002000;
          return;
        }
        uVar5 = 1;
        goto LAB_ram_000038d0;
      }
      DAT_ram_20002f89 = DAT_ram_200041a1;
      if (DAT_ram_200041a1 == '\x01') {
        FUN_ram_0000566a();
      }
      else if ((DAT_ram_200041a1 == '\0' && DAT_ram_20003a48 == '\0') && (DAT_ram_20002f8a != '\0'))
      {
        FUN_ram_000055c0();
      }
      if (DAT_ram_20002f89 == '\x02') {
        auStack_128[0] = 0;
LAB_ram_00003a9c:
        (*_DAT_ram_00040174)(0x305,1,auStack_128);
      }
      else if (DAT_ram_20002f89 == '\0') {
        auStack_128[0] = 1;
        goto LAB_ram_00003a9c;
      }
      uVar5 = 0x51;
      goto LAB_ram_000038d0;
    }
    if (bVar1 == 0xef) {
      if (DAT_ram_200041a1 == '*') {
        gp = &DAT_ram_20002000;
        DAT_ram_20002fb4 = 1;
        return;
      }
      if (DAT_ram_200041a1 != ',') {
        gp = &DAT_ram_20002000;
        return;
      }
      gp = &DAT_ram_20002000;
      DAT_ram_20002fb4 = 0;
      return;
    }
    if (bVar1 < 0xf0) {
      if (bVar1 != 0xe0) {
        gp = &DAT_ram_20002000;
        return;
      }
      _DAT_ram_2000409c = 0x33504de1;
      DAT_ram_200040a0 = 0x423530;
      DAT_ram_200040a4 = 0x66000100;
      DAT_ram_200040b0 = 0x33504d0f;
      DAT_ram_200040b4 = 0x423530;
      DAT_ram_200040b8 = 0;
      DAT_ram_200040ba = 0;
      DAT_ram_200040a8 = 0x100;
      DAT_ram_200040ac = 0x100;
      DAT_ram_2000409a = 0x1f;
      goto LAB_ram_00003a34;
    }
    if (bVar1 == 0xf0) {
      if (DAT_ram_200041a1 != -0x54) {
        gp = &DAT_ram_20002000;
        return;
      }
      _DAT_ram_2000409c = CONCAT22(_DAT_ram_2000409e,0xf1);
      DAT_ram_2000409a = 2;
      if (DAT_ram_20002fb8 == 1) goto LAB_ram_00003a34;
      DAT_ram_20002fb8 = 1;
      DAT_ram_20002fb6 = 100;
    }
    else {
      if (bVar1 != 0xfc) {
        gp = &DAT_ram_20002000;
        return;
      }
      if (DAT_ram_200041a1 != '*') {
        gp = &DAT_ram_20002000;
        return;
      }
      _DAT_ram_2000409c = CONCAT22(_DAT_ram_2000409e,0x3fd);
      if ((uint)DAT_ram_200041a2 + (uint)DAT_ram_200041a3 + (uint)DAT_ram_200041a4 +
          (uint)DAT_ram_200041a5 != 0) {
        (*_DAT_ram_00040048)(auStack_140,0xff,0x16);
        (*_DAT_ram_00040048)(auStack_128,0xff,0x16);
        FUN_ram_200028d6(0xb,0x6e00,auStack_128,0x16);
        iVar3 = (*_DAT_ram_0004003c)(auStack_132,auStack_11a,4);
        if (iVar3 == 0) {
          iVar3 = (*_DAT_ram_0004003c)(auStack_11a,&DAT_ram_200041a2,8);
          if (iVar3 != 0) goto LAB_ram_000039ec;
          (*_DAT_ram_0004004c)(auStack_11a,&DAT_ram_200041a2,8);
          FUN_ram_200028d6(9,0x6e00,0,0x100);
        }
        else {
          (*_DAT_ram_0004004c)(auStack_11a,&DAT_ram_200041a2,8);
          FUN_ram_200028d6(9,0x6e00,0,0x100);
        }
        FUN_ram_200028d6(10,0x6e00,auStack_128,0x16);
      }
LAB_ram_000039ec:
      FUN_ram_00007532(&DAT_ram_200041aa);
    }
  }
  DAT_ram_2000409a = 2;
LAB_ram_00003a34:
  DAT_ram_20004098 = DAT_ram_2000419c >> 8 | DAT_ram_2000419c << 8;
  uVar2 = encode_transport_frame(&DAT_ram_20004098,&DAT_ram_20004098,auStack_110);
  (*param_1)(auStack_110,uVar2);
  return;
}

