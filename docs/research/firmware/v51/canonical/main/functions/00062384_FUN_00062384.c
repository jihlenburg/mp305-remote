/* Address: 00062384; name: FUN_00062384; body bytes: 3164 */

void FUN_00062384(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined **ppuVar6;
  
  iVar1 = DAT_2003a5d0;
  iVar2 = FUN_0004bc8c(param_2);
  if (iVar2 == 0) {
LAB_00062fba:
    iVar2 = iVar1 + 0x40;
    goto LAB_0006240a;
  }
  iVar3 = FUN_0004b132(param_2,&DAT_00067170);
  if (iVar3 == 0) {
    iVar3 = FUN_0004b132(param_2,&DAT_0007a5bc);
    if (iVar3 == 0) {
      iVar3 = FUN_0004b132(param_2,&DAT_0007ab24);
      if (iVar3 != 0) {
        ppuVar6 = (undefined **)0x0;
        iVar2 = iVar1 + 0x22c;
        goto LAB_000630c4;
      }
      iVar3 = FUN_0004b132(param_2,&PTR_DAT_0007a5fc);
      if (iVar3 != 0) {
        iVar2 = FUN_0004b132(iVar2,&DAT_0007a620);
        if (iVar2 == 0) {
          FUN_0004ab24(param_2,iVar1 + 100,0);
          FUN_0004ab24(param_2,iVar1 + 0x130,4);
          iVar2 = iVar1 + 0x13c;
          FUN_0004ab24(param_2,iVar2,8);
          FUN_0004ab24(param_2,iVar1 + 0x70,&LAB_00050000);
          FUN_0004ab24(param_2,iVar1 + 0xd0,0x50080);
          FUN_0004ab24(param_2,iVar1 + 0xc4,0x50020);
          FUN_0004ab24(param_2,iVar1 + 0x7c,&LAB_00050000_1);
          FUN_0004ab24(param_2,iVar1 + 0x130,0x50004);
          ppuVar6 = (undefined **)0x50008;
        }
        else {
          FUN_0004ab24(param_2,iVar1 + 0x25c,0);
          FUN_0004ab24(param_2,iVar1 + 0x130,4);
          iVar2 = iVar1 + 0x13c;
          FUN_0004ab24(param_2,iVar2,8);
          FUN_0004ab24(param_2,iVar1 + 0x268,&LAB_00050000);
          FUN_0004ab24(param_2,iVar1 + 0xc4,0x50020);
          FUN_0004ab24(param_2,iVar1 + 0xd0,0x50080);
          FUN_0004ab24(param_2,iVar1 + 0x130,0x50004);
          ppuVar6 = (undefined **)0x50008;
        }
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007a598);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0x88,0);
        iVar2 = iVar1 + 0x148;
        FUN_0004ab24(param_2,iVar2,0);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        FUN_0004ab24(param_2,iVar1 + 0x7c,0x20000);
        ppuVar6 = (undefined **)0x20000;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007ae60);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0x88,0);
        FUN_0004ab24(param_2,iVar1 + 0x148,0);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        FUN_0004ab24(param_2,iVar1 + 0x7c,0x20000);
        FUN_0004ab24(param_2,iVar1 + 0x148,0x20000);
        FUN_0004ab24(param_2,iVar1 + 0x1b4,0x30000);
        FUN_0004ab24(param_2,iVar1 + 0x178,0x30020);
        FUN_0004ab24(param_2,iVar1 + 0x184,0x30000);
        ppuVar6 = (undefined **)0x30020;
        iVar2 = iVar1 + 400;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007aef0);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        FUN_0004ab24(param_2,iVar1 + 0xdc,0);
        FUN_0004ab24(param_2,iVar1 + 0x154,0);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        FUN_0004ab24(param_2,iVar1 + 0x4c,0x10000);
        FUN_0004ab24(param_2,iVar1 + 0x58,&PTR_FUN_00016dc4_1_00010040);
        FUN_0004ab24(param_2,iVar1 + 0xb8,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0x238,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0x100,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0xc4,0x50020);
        FUN_0004ab24(param_2,iVar1 + 0x7c,0x50004);
        iVar2 = iVar1 + 0x94;
        ppuVar6 = (undefined **)0x50008;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007a6b0);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0x10c,0);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0xd0,0x20080);
        FUN_0004ab24(param_2,iVar1 + 0x208,0x20000);
        FUN_0004ab24(param_2,iVar1 + 0x7c,0x20001);
        FUN_0004ab24(param_2,iVar1 + 0x214,0x20001);
        FUN_0004ab24(param_2,iVar1 + 0xc4,0x20020);
        FUN_0004ab24(param_2,iVar1 + 0x178,0x20020);
        FUN_0004ab24(param_2,iVar1 + 400,0x20020);
        ppuVar6 = (undefined **)0x20000;
        iVar2 = iVar1 + 0x184;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007aecc);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0xac,0);
        FUN_0004ab24(param_2,iVar1 + 0x148,0);
        FUN_0004ab24(param_2,iVar1 + 0x1a8,0);
        iVar2 = iVar1 + 0xd0;
        FUN_0004ab24(param_2,iVar2,0x80);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x7c,0x20001);
        FUN_0004ab24(param_2,iVar1 + 0x148,0x20000);
        FUN_0004ab24(param_2,iVar2,0x20080);
        FUN_0004ab24(param_2,iVar1 + 0x1b4,0x30000);
        FUN_0004ab24(param_2,iVar1 + 0xb8,0x30000);
        FUN_0004ab24(param_2,iVar1 + 0x220,0x30000);
        FUN_0004ab24(param_2,iVar2,0x30080);
        iVar2 = iVar1 + 400;
        FUN_0004ab24(param_2,iVar2,0x20001);
        ppuVar6 = (undefined **)0x20000;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007a68c);
      ppuVar6 = (undefined **)0x60000;
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        FUN_0004ab24(param_2,iVar1 + 0xf4,0);
        FUN_0004ab24(param_2,iVar1 + 0x1f0,0);
        FUN_0004ab24(param_2,iVar1 + 0x4c,0x10000);
        FUN_0004ab24(param_2,iVar1 + 0x58,&PTR_FUN_00016dc4_1_00010040);
        iVar2 = iVar1 + 0x1d8;
        FUN_0004ab24(param_2,iVar2,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0x1e4,0x20000);
        ppuVar6 = (undefined **)0x60000;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007adf4);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        FUN_0004ab24(param_2,iVar1 + 0x19c,0);
        FUN_0004ab24(param_2,iVar1 + 0x118,0);
        FUN_0004ab24(param_2,iVar1 + 0x124,0);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        ppuVar6 = (undefined **)0x40000;
        goto LAB_00062e1e;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007a6d4);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        FUN_0004ab24(param_2,iVar1 + 0xf4,0);
        FUN_0004ab24(param_2,iVar1 + 0x184,0);
        iVar2 = iVar1 + 400;
        FUN_0004ab24(param_2,iVar2,0x20);
        FUN_0004ab24(param_2,iVar1 + 0xc4,0x20);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        uVar5 = 0x20000;
LAB_00062f64:
        FUN_0004ab24(param_2,iVar2,uVar5);
        ppuVar6 = (undefined **)0x80;
        iVar2 = iVar1 + 0xd0;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007a6f8);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        FUN_0004ab24(param_2,iVar1 + 0x160,0);
        FUN_0004ab24(param_2,iVar1 + 0x118,0);
        FUN_0004ab24(param_2,iVar1 + 0x1fc,0);
        FUN_0004ab24(param_2,iVar1 + 0x4c,0x10000);
        FUN_0004ab24(param_2,iVar1 + 0x58,&PTR_FUN_00016dc4_1_00010040);
        FUN_0004ab24(param_2,iVar1 + 0xb8,0x40000);
        FUN_0004ab24(param_2,iVar1 + 0x7c,0x40001);
        ppuVar6 = (undefined **)0x40020;
LAB_00062d9a:
        iVar2 = iVar1 + 0xc4;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007a574);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0x1c0,0);
        FUN_0004ab24(param_2,iVar1 + 0x1c0,0x20000);
        FUN_0004ab24(param_2,iVar1 + 0x1cc,0x20000);
        ppuVar6 = (undefined **)0x30000;
        iVar2 = iVar1 + 0x1b4;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007aea8);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0x1c0,0);
        FUN_0004ab24(param_2,iVar1 + 0x1c0,0x20000);
        ppuVar6 = (undefined **)0x20000;
        iVar2 = iVar1 + 0x1cc;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007af38);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        FUN_0004ab24(param_2,iVar1 + 0xf4,0);
        FUN_0004ab24(param_2,iVar1 + 0xd0,0x80);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        FUN_0004ab24(param_2,iVar1 + 0x4c,0x10000);
        FUN_0004ab24(param_2,iVar1 + 0x58,&PTR_FUN_00016dc4_1_00010040);
        FUN_0004ab24(param_2,iVar1 + 0x244,0x60002);
        ppuVar6 = (undefined **)0x80000;
        iVar2 = iVar1 + 0x250;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007a620);
      if (iVar2 != 0) {
        iVar2 = iVar1 + 100;
LAB_00062ff0:
        FUN_0004ab24(param_2,iVar2,0);
        ppuVar6 = (undefined **)0x0;
        iVar2 = iVar1 + 0xdc;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007a644);
      if ((iVar2 != 0) || (iVar2 = FUN_0004b132(param_2,&DAT_0007a668), iVar2 != 0)) {
        ppuVar6 = (undefined **)0x0;
        iVar2 = iVar1 + 0x274;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007a740);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0x40,0);
        if (*(char *)(iVar1 + 0x28) == '\x01') {
          iVar2 = iVar1 + 0xf4;
        }
        else {
          iVar2 = iVar1 + 0xe8;
        }
        FUN_0004ab24(param_2,iVar2,0);
        FUN_0004ab24(param_2,iVar1 + 0x130,4);
        FUN_0004ab24(param_2,iVar1 + 0x13c,8);
        FUN_0004ab24(param_2,iVar1 + 0x70,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0xd0,0x50080);
        FUN_0004ab24(param_2,iVar1 + 0xb8,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0x304,&LAB_00050000);
        FUN_0004ab24(param_2,iVar1 + 0xc4,0x50020);
        FUN_0004ab24(param_2,iVar1 + 0xac,&LAB_00050000_1);
        FUN_0004ab24(param_2,iVar1 + 0x88,0x50004);
        iVar2 = iVar1 + 0xa0;
        ppuVar6 = (undefined **)0x50008;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007ab48);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        iVar2 = iVar1 + 0x310;
        goto LAB_0006240a;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007ab90);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0xac,0);
        ppuVar6 = (undefined **)0x0;
        iVar2 = iVar1 + 0x328;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007ab6c);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 0xb8,0);
        FUN_0004ab24(param_2,iVar1 + 0x31c,0);
        FUN_0004ab24(param_2,iVar1 + 0x7c,4);
        FUN_0004ab24(param_2,iVar1 + 0x328,4);
        FUN_0004ab24(param_2,iVar1 + 0x328,0x20);
        ppuVar6 = (undefined **)0x20;
        goto LAB_00062d9a;
      }
      iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007abb4);
      if (iVar2 != 0) {
        FUN_0004ab24(param_2,iVar1 + 100,0);
        ppuVar6 = (undefined **)0x0;
        iVar2 = iVar1 + 0x280;
        goto LAB_000630c4;
      }
      iVar2 = FUN_0004b132(param_2,&DAT_0007ac68);
      if (iVar2 == 0) {
        iVar2 = FUN_0004b132(param_2,&DAT_0007ac8c);
        if (iVar2 != 0) {
          iVar2 = iVar1 + 0x2a4;
          goto LAB_0006240a;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007abfc);
        if (iVar2 != 0) {
          FUN_0004ab24(param_2,iVar1 + 0x28c,0);
          FUN_0004ab24(param_2,iVar1 + 0x2e0,0x20);
          FUN_0004ab24(param_2,iVar1 + 0x88,0x21);
          FUN_0004ab24(param_2,iVar1 + 0x88,1);
          ppuVar6 = (undefined **)0x4;
LAB_00062e1e:
          iVar2 = iVar1 + 0x7c;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007acd4);
        if ((iVar2 != 0) || (iVar2 = FUN_0004b132(param_2,&DAT_0007acb0), iVar2 != 0)) {
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 700;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007abd8);
        if (iVar2 != 0) {
          iVar2 = iVar1 + 0x2b0;
          goto LAB_0006240a;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007ac20);
        if (iVar2 != 0) {
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0x2d4;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007ac44);
        if (iVar2 != 0) {
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0x2ec;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007acf8);
        if (iVar2 != 0) {
          FUN_0004ab24(param_2,iVar1 + 100,0);
          FUN_0004ab24(param_2,iVar1 + 0xdc,0);
LAB_00063008:
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0x160;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007add0);
        if (iVar2 != 0) {
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0x2f8;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007ad1c);
        if (iVar2 != 0) {
          FUN_0004ab24(param_2,iVar1 + 0xe8,0);
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0xac;
          goto LAB_000630c4;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007ad64);
        if (iVar2 != 0) goto LAB_00062ed6;
        iVar2 = FUN_0004b132(param_2,&DAT_0007ad40);
        if (iVar2 != 0) {
          FUN_0004ab24(param_2,iVar1 + 0x4c,0x10000);
          ppuVar6 = &PTR_FUN_00016dc4_1_00010040;
          iVar2 = iVar1 + 0x58;
          goto LAB_00062efa;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007adac);
        if ((iVar2 != 0) || (iVar2 = FUN_0004b132(param_2,&DAT_0007ad88), iVar2 != 0)) {
          FUN_0004ab24(param_2,iVar1 + 0x70,0);
          FUN_0004ab24(param_2,iVar1 + 0x7c,0);
          FUN_0004ab24(param_2,iVar1 + 0x184,0);
          FUN_0004ab24(param_2,iVar1 + 0xc4,0x20);
          FUN_0004ab24(param_2,iVar1 + 400,0x20);
          FUN_0004ab24(param_2,iVar1 + 0x130,4);
          uVar5 = 1;
          iVar2 = iVar1 + 0x94;
          goto LAB_00062f64;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007ae84);
        if (iVar2 != 0) {
          FUN_0004ab24(param_2,iVar1 + 100,0);
          FUN_0004ab24(param_2,iVar1 + 0xf4,0);
          FUN_0004ab24(param_2,iVar1 + 0x130,4);
          FUN_0004ab24(param_2,iVar1 + 0x13c,8);
          goto LAB_00062e1e;
        }
        iVar2 = FUN_0004b132(param_2,&DAT_0007af5c);
        if (iVar2 != 0) goto LAB_00062fba;
        iVar2 = FUN_0004b132(param_2,&DAT_0007af80);
        if (iVar2 == 0) {
          iVar2 = FUN_0004b132(param_2,&DAT_0007af14);
          if (iVar2 != 0) {
            iVar2 = iVar1 + 0x40;
            goto LAB_00062ff0;
          }
          iVar2 = FUN_0004b132(param_2,&DAT_0007afa4);
          if (iVar2 == 0) {
            iVar2 = FUN_0004b132(param_2,&DAT_0007ab00);
            if (iVar2 == 0) {
              iVar2 = FUN_0004b132(param_2,&PTR_DAT_0007ae3c);
              if (iVar2 == 0) {
                return;
              }
              iVar2 = iVar1 + 0x358;
              FUN_0004ab24(param_2,iVar2,0);
              FUN_0004ab24(param_2,iVar2,0x20000);
              ppuVar6 = (undefined **)&LAB_00050000;
            }
            else {
              ppuVar6 = (undefined **)0x0;
              iVar2 = iVar1 + 0x34c;
            }
            goto LAB_000630c4;
          }
          goto LAB_00063008;
        }
      }
      else {
        iVar2 = iVar1 + 0x298;
LAB_0006240a:
        FUN_0004ab24(param_2,iVar2,0);
      }
      FUN_0004ab24(param_2,iVar1 + 0x4c,0x10000);
      ppuVar6 = &PTR_FUN_00016dc4_1_00010040;
      iVar2 = iVar1 + 0x58;
      goto LAB_000630c4;
    }
    iVar3 = FUN_0004bc8c(iVar2);
    if (((iVar3 == 0) || (iVar4 = FUN_0004b9de(iVar3,0), iVar4 != iVar2)) ||
       (iVar3 = FUN_0004b132(iVar3,&DAT_0007af14), iVar3 == 0)) {
      FUN_0004ab24(param_2,iVar1 + 0x70,0);
      FUN_0004ab24(param_2,iVar1 + 0x7c,0);
      FUN_0004ab24(param_2,iVar1 + 0x184,0);
      FUN_0004ab24(param_2,iVar1 + 0xc4,0x20);
      FUN_0004ab24(param_2,iVar1 + 400,0x20);
      FUN_0004ab24(param_2,iVar1 + 0x130,4);
      FUN_0004ab24(param_2,iVar1 + 0x178,0x20);
      FUN_0004ab24(param_2,iVar1 + 0x94,1);
      FUN_0004ab24(param_2,iVar1 + 0xd0,0x80);
      iVar3 = FUN_0004b132(iVar2,&DAT_0007acd4);
      if ((iVar3 == 0) && (iVar2 = FUN_0004b132(iVar2,&DAT_0007acb0), iVar2 == 0)) {
        return;
      }
      FUN_0004ab24(param_2,iVar1 + 0x2c8,0);
      ppuVar6 = (undefined **)0x20;
      iVar2 = iVar1 + 0x2e0;
      goto LAB_000630c4;
    }
    FUN_0004ab24(param_2,iVar1 + 0xc4,0x20);
    FUN_0004ab24(param_2,iVar1 + 0x88,1);
    FUN_0004ab24(param_2,iVar1 + 0x340,1);
    FUN_0004ab24(param_2,iVar1 + 0x130,4);
    uVar5 = 8;
    iVar2 = iVar1 + 0x13c;
  }
  else {
    iVar3 = FUN_0004b132(iVar2,&DAT_0007af14);
    if ((iVar3 != 0) && (iVar3 = FUN_0004b9de(iVar2,1), iVar3 == param_2)) {
      return;
    }
    iVar3 = FUN_0004b132(iVar2,&DAT_0007af14);
    if ((iVar3 == 0) || (iVar3 = FUN_0004b9de(iVar2,0), iVar3 != param_2)) {
      uVar5 = FUN_0004bc8c(iVar2);
      iVar3 = FUN_0004b132(uVar5,&DAT_0007af14);
      if (iVar3 == 0) {
        iVar3 = FUN_0004b132(iVar2,&DAT_0007afa4);
        if ((iVar3 != 0) && (iVar3 = FUN_0004b9de(iVar2,0), iVar3 == param_2)) {
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0xac;
LAB_00062efa:
          FUN_0004ab24(param_2,iVar2,ppuVar6);
LAB_00062ed6:
          ppuVar6 = (undefined **)0x0;
          iVar2 = iVar1 + 0xe8;
          goto LAB_000630c4;
        }
        iVar3 = FUN_0004b132(iVar2,&DAT_0007afa4);
        if ((iVar3 == 0) || (iVar3 = FUN_0004b9de(iVar2,1), iVar3 != param_2)) {
          iVar2 = FUN_0004b132(iVar2,&DAT_0007a620);
          if (iVar2 != 0) {
            return;
          }
          iVar2 = iVar1 + 100;
        }
        else {
          FUN_0004ab24(param_2,iVar1 + 0x40,0);
          iVar2 = iVar1 + 0x100;
        }
      }
      else {
        FUN_0004ab24(param_2,iVar1 + 0x100,0);
        iVar2 = iVar1 + 0x16c;
      }
      goto LAB_0006240a;
    }
    FUN_0004ab24(param_2,iVar1 + 0xb8,0);
    uVar5 = 4;
    iVar2 = iVar1 + 0x130;
  }
  FUN_0004ab24(param_2,iVar2,uVar5);
  ppuVar6 = (undefined **)0x4;
  iVar2 = iVar1 + 0x334;
LAB_000630c4:
  FUN_0004ab24(param_2,iVar2,ppuVar6);
  return;
}

