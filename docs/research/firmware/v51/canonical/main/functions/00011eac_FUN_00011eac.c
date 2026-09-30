/* Address: 00011eac; name: FUN_00011eac; body bytes: 586 */

void FUN_00011eac(short param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined2 *extraout_r2;
  undefined2 *extraout_r2_00;
  undefined2 *extraout_r2_01;
  undefined1 *puVar5;
  undefined8 uVar6;
  undefined1 auStack_c8 [160];
  uint local_28;
  
  cVar1 = DAT_1fff9b9b;
  local_28 = (uint)DAT_1fff9b9a;
  if (DAT_1ffe018b != '\0') {
    return;
  }
  DAT_1fff9ba8 = DAT_1fff9ba8 + param_1;
  if (499 < DAT_1fff9ba8) {
    DAT_1fff9ba8 = 0;
  }
  if ((((0 < DAT_1fff9baa) && (iVar3 = get_output_enabled(), iVar3 != 0)) && (cVar1 == '\x02')) &&
     (current_mode == '\x02')) {
    DAT_1fff9baa = DAT_1fff9baa - param_1;
  }
  puVar4 = (undefined1 *)FUN_00015fa4(0);
  puVar5 = puVar4 + 4;
  FUN_0001049c(auStack_c8,0xa0);
  iVar3 = 0;
  if ((DAT_1fff9bbe == '\0') || (DAT_1fff9b91 == '\0')) {
    if ((DAT_1fff9bbb != '\0') && (DAT_1fff9b91 != '\0')) {
      iVar3 = FUN_00011858(puVar5);
      *extraout_r2 = 0;
      *(undefined1 *)((int)extraout_r2 + 0x13) = 0;
      goto LAB_00011ff6;
    }
    if ((DAT_1fff9bb9 != '\0') && (DAT_1fff9b91 != '\0')) {
      if (DAT_1fffaaf4 == '\0') {
        iVar3 = FUN_00011e3c(puVar5,0,&DAT_1fff9ba8);
      }
      DAT_1fff9ba8 = 0;
      DAT_1fff9bb9 = '\0';
      goto LAB_00011ff6;
    }
    if ((DAT_1fff9bbc != '\0') && (DAT_1fff9b91 != '\0')) {
      iVar3 = FUN_00011830(puVar5);
      *extraout_r2_00 = 0;
      *(undefined1 *)(extraout_r2_00 + 10) = 0;
      goto LAB_00011ff6;
    }
    if ((DAT_1fff9bbd != '\0') && (DAT_1fff9b91 != '\0')) {
      iVar3 = FUN_0001183c(puVar5);
      DAT_1fff9ba8 = 0;
      DAT_1fff9bbd = '\0';
      goto LAB_00011ff6;
    }
    if ((DAT_1ffe018f != cVar1) && (cVar1 == '\x02')) {
      uVar6 = get_output_enabled(DAT_1ffe018f,0,&DAT_1fff9ba8);
      if (((int)uVar6 != 0) && ((DAT_1fff9baa < 1 && (current_mode == '\x02')))) {
        iVar3 = FUN_00011824(puVar5,(int)((ulonglong)uVar6 >> 0x20),&DAT_1fff9ba8);
        *extraout_r2_01 = 0;
        extraout_r2_01[1] = 3000;
        DAT_1ffe018f = '\x02';
        goto LAB_00011ff6;
      }
    }
    if (DAT_1fff9ba8 != 0) goto LAB_0001201a;
    if (DAT_1fff9b91 == '\0') {
      if (0x14 < DAT_1ffe018e) goto LAB_0001201a;
      iVar3 = 1;
      *puVar5 = 0;
      DAT_1ffe018e = DAT_1ffe018e + 1;
    }
    else if ((local_28 == 1) && (DAT_1fff9bb0 == 0)) {
      iVar3 = 2;
      *puVar5 = 0xb6;
      puVar4[5] = 0;
    }
    else {
      if (DAT_1fff9bb8 == -0x48) {
        *puVar5 = 0xb8;
        puVar4[5] = 0;
        puVar4[6] = 0xe0;
        puVar4[7] = 0x2e;
        puVar4[8] = 0xe4;
        puVar4[9] = 0xc;
        iVar3 = 6;
      }
      else {
        if (DAT_1fff9bb8 != -0x46) {
          if (DAT_1fffaaf4 != '\0') {
            DAT_1fffaaf4 = '\0';
            DAT_1fffaaf6 = 1;
            DAT_1fffaaf8 = 0;
            DAT_1fff9bb9 = '\x01';
            goto LAB_0001201a;
          }
          *puVar5 = 0xb0;
          puVar4[5] = DAT_1fff9bb5;
          puVar4[6] = DAT_1fff9bb4;
          puVar4[7] = DAT_1fff9bb6;
          puVar4[8] = DAT_1fffaa23;
          iVar3 = 5;
          goto LAB_00011ff8;
        }
        *puVar5 = 0xba;
        puVar4[5] = 0;
        puVar4[6] = 0xe4;
        puVar4[7] = 0xc;
        puVar4[8] = 0xf8;
        puVar4[9] = 0x2a;
        puVar4[10] = 0xb8;
        puVar4[0xb] = 0xb;
        iVar3 = 8;
      }
      DAT_1fff9bb8 = '\0';
    }
  }
  else {
    iVar3 = FUN_000118f8(puVar5);
    DAT_1fff9ba8 = 0;
    DAT_1fff9bbe = '\0';
    DAT_1fffabbc = 0;
LAB_00011ff6:
    if (iVar3 == 0) goto LAB_0001201a;
  }
LAB_00011ff8:
  puVar4[2] = (char)iVar3;
  puVar4[1] = 4;
  *puVar4 = 2;
  uVar2 = encode_transport_frame(0,puVar4,auStack_c8);
  FUN_0001f1f4(auStack_c8,uVar2);
LAB_0001201a:
  if (((cVar1 != '\x02') || (iVar3 = get_output_enabled(), iVar3 == 0)) || (current_mode != '\x02'))
  {
    DAT_1ffe018f = '\0';
    DAT_1fffaaeb = 0;
    DAT_1fff9baa = 3000;
    DAT_1fff9bac = 0;
  }
  return;
}

