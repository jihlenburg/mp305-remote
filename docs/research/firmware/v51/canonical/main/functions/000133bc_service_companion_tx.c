/* Address: 000133bc; name: service_companion_tx; body bytes: 1642 */

/* Companion transmit scheduling, retries, bind and remote-control notifications. */

void service_companion_tx(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 local_28;
  
  DAT_1ffe01c0 = DAT_1ffe01c0 + param_1;
  local_28 = param_4;
  if (DAT_1ffe0184 == '\0') goto LAB_000139d2;
  if (DAT_1ffe0186 != '\0') {
    if (0x31 < DAT_1ffe0196) {
      DAT_1ffe0186 = 0;
      DAT_1ffe0196 = 0;
      DAT_1ffe019c = 0;
      DAT_1fffaacf = 0;
      return;
    }
    if (((uint)DAT_1ffe019c + param_1 & 0xffff) < 100) {
      DAT_1ffe019c = (short)((uint)DAT_1ffe019c + param_1);
      return;
    }
    DAT_1ffe019c = 0;
    DAT_1ffe0196 = DAT_1ffe0196 + 1;
    FUN_0001e24c(&DAT_4001d400,1,&DAT_1fff9556,DAT_1fff9656);
    goto LAB_000139d2;
  }
  if ((DAT_1fff9448 != '\0') && (DAT_1ffe0185 == 0)) {
    DAT_1ffe01a0 = 10000;
    DAT_1fff9448 = '\0';
    FUN_0001e24c(&DAT_4001d400,1,&DAT_1fff944a,DAT_1fff954a);
    FUN_0001046a(&DAT_1fff9554,&DAT_1fff9448,0x10c);
    DAT_1ffe0184 = '\0';
    DAT_1ffe019c = 0;
    goto LAB_000139d2;
  }
  if ((DAT_1fffaacf != DAT_1ffe018c) && ((DAT_1fffab1c != '\0' && (DAT_1fff9449 != '\0')))) {
    puVar1 = (undefined1 *)FUN_00015fa4(1);
    puVar1[4] = 0x50;
    puVar1[5] = DAT_1fffaacf;
    puVar1[2] = 2;
    puVar1[1] = 3;
    *puVar1 = 2;
    DAT_1fff954a = encode_transport_frame(1,puVar1,&DAT_1fff944a);
    FUN_0001e24c(&DAT_4001d400,1,&DAT_1fff944a);
    FUN_0001046a(&DAT_1fff9554,&DAT_1fff9448,0x10c);
    DAT_1ffe0184 = '\0';
    DAT_1fff954b = 1;
    DAT_1fff9440 = 1000;
    DAT_1ffe019c = 0;
    DAT_1ffe018c = DAT_1fffaacf;
    goto LAB_000139d2;
  }
  if (((DAT_1fff9550 == 0) || (DAT_1fffa00c != '\0')) &&
     ((((DAT_1fff9449 != '\0' && (DAT_1fffa00e != '\x01')) && (DAT_1ffe0185 == 0)) &&
      (DAT_1ffe01c0 < 10000)))) goto LAB_000139d2;
  puVar1 = (undefined1 *)FUN_00015fa4(1);
  DAT_1ffe019c = 0;
  puVar2 = puVar1 + 4;
  local_28 = (uint)DAT_1ffe0185;
  iVar5 = 0;
  if (local_28 != 0) {
    if (0x31 < DAT_1ffe0198) {
      DAT_1ffe0185 = 0;
      DAT_1ffe0198 = 0;
      DAT_1ffe019a = 0;
      DAT_1ffe019c = 0;
      DAT_1fffaacf = 0;
      return;
    }
    if (((uint)DAT_1ffe019a + param_1 & 0xffff) < 100) {
      DAT_1ffe019a = (short)((uint)DAT_1ffe019a + param_1);
      DAT_1ffe019c = 0;
      return;
    }
  }
  DAT_1ffe019a = 0;
  if ((DAT_1fffa00e == '\x01') || ((int)(DAT_1fff9550 << 0x11) < 0)) {
    if ((DAT_1ffe019e != 0) && (-1 < (int)(DAT_1fff9550 << 0x11))) {
LAB_00013578:
      DAT_1ffe019e = DAT_1ffe019e + -1;
      goto LAB_000139d2;
    }
    DAT_1ffe019e = 500;
    *puVar2 = 0xf0;
    puVar1[5] = 0xac;
    puVar1[1] = 3;
    iVar5 = 2;
    DAT_1fff9550 = DAT_1fff9550 & 0xffffbfff;
  }
  else if ((DAT_1fff9449 == '\0') && (DAT_1ffe018d < 0x15)) {
    if (DAT_1ffe019e != 0) goto LAB_00013578;
    DAT_1ffe019e = 500;
    if (DAT_1fff9434 == '\0') {
      *puVar2 = 0xe0;
      iVar5 = 1;
      puVar1[1] = 3;
    }
    else {
      *puVar2 = 0xfc;
      puVar1[5] = 0x2a;
      puVar1[6] = 0x4d;
      puVar1[7] = 0x50;
      puVar1[8] = 0x33;
      puVar1[9] = 0x30;
      puVar1[10] = 0x35;
      puVar1[0xb] = 0x42;
      puVar1[0xc] = 0x20;
      puVar1[0xd] = 0x20;
      puVar1[0xe] = 1;
      puVar1[0xf] = 0x35;
      puVar1[0x10] = 2;
      puVar1[0x11] = 0;
      puVar1[1] = 3;
      DAT_1ffe018d = DAT_1ffe018d + 1;
      iVar5 = 0xe;
    }
  }
  else {
    if (DAT_1fffa00c != DAT_1ffe0195) goto LAB_000139d2;
    if (local_28 == 0) {
      if (((DAT_1fff9550 & 1) == 0) || (DAT_1fff9449 == '\0')) {
        if ((int)(DAT_1fff9550 << 0x12) < 0) {
          *puVar2 = 0xe0;
          puVar1[1] = 3;
          iVar5 = 1;
          DAT_1fff9550 = DAT_1fff9550 & 0xffffdfff;
        }
        else {
          if ((int)(DAT_1fff9550 << 0x18) < 0) {
            local_28 = (uint)CONCAT12(DAT_1ffe0189,CONCAT11(DAT_1ffe0188,0xd8));
            if (DAT_1fffaacf == '\x01') {
              puVar1[1] = 6;
            }
            else {
              if (DAT_1fffaacf != '\x02') {
                DAT_1ffe0187 = 0;
                DAT_1ffe019a = 0;
                DAT_1ffe019c = 0;
                DAT_1fff9550 = DAT_1fff9550 & 0xffffff7f;
                return;
              }
              puVar1[1] = 1;
            }
            iVar5 = FUN_00015ca0(&local_28,3,puVar2,puVar1[1]);
            if ((byte)(&DAT_1fffa3f4)[DAT_1ffe0188] <= DAT_1ffe0187) {
              DAT_1fff9550 = DAT_1fff9550 & 0xffffff7f;
            }
          }
          else if ((int)(DAT_1fff9550 << 0x16) < 0) {
            local_28 = 0x31dc;
            if (DAT_1fffaacf == '\x01') {
              puVar1[1] = 6;
            }
            else {
              if (DAT_1fffaacf != '\x02') {
                DAT_1ffe019a = 0;
                DAT_1ffe019c = 0;
                DAT_1fff9550 = DAT_1fff9550 & 0xfffffdff;
                return;
              }
              puVar1[1] = 1;
            }
            iVar5 = cmd_dc(&local_28,2,puVar2,puVar1[1]);
            DAT_1fff9550 = DAT_1fff9550 & 0xfffffdff;
          }
          else if ((int)(DAT_1fff9550 << 0x17) < 0) {
            *puVar2 = 0xdb;
            puVar1[5] = 0;
            if (DAT_1fffaacf == '\x01') {
              puVar1[1] = 6;
              puVar1[6] = 0x31;
              iVar5 = 3;
            }
            else if (DAT_1fffaacf == '\x02') {
              puVar1[1] = 1;
              iVar5 = 2;
            }
            DAT_1fff9550 = DAT_1fff9550 & 0xfffffeff;
          }
          else if ((int)(DAT_1fff9550 << 0x15) < 0) {
            local_28 = 0x31e4;
            if (DAT_1fffaacf == '\x01') {
              puVar1[1] = 6;
            }
            else {
              if (DAT_1fffaacf != '\x02') {
                DAT_1ffe019a = 0;
                DAT_1ffe019c = 0;
                DAT_1fff9550 = DAT_1fff9550 & 0xfffffbff;
                return;
              }
              puVar1[1] = 1;
            }
            iVar5 = cmd_e4(&local_28,2,puVar2,puVar1[1]);
            DAT_1fff9550 = DAT_1fff9550 & 0xfffffbff;
          }
          else if ((int)(DAT_1fff9550 << 0x14) < 0) {
            local_28 = 0x31ea;
            if (DAT_1fffaacf == '\x01') {
              puVar1[1] = 6;
            }
            else {
              if (DAT_1fffaacf != '\x02') {
                DAT_1ffe019a = 0;
                DAT_1ffe019c = 0;
                DAT_1fff9550 = DAT_1fff9550 & 0xfffff7ff;
                return;
              }
              puVar1[1] = 1;
            }
            iVar5 = cmd_ea(&local_28,2,puVar2,puVar1[1]);
            DAT_1fff9550 = DAT_1fff9550 & 0xfffff7ff;
          }
          else if ((int)(DAT_1fff9550 << 0x1e) < 0) {
            puVar1[1] = DAT_1ffe018a;
            iVar5 = build_bind_reply();
            DAT_1fff9550 = DAT_1fff9550 & 0xfffffffd;
            bind_pending = 0;
            bind_decision = 0;
          }
          else {
            if (-1 < (int)(DAT_1fff9550 << 0x1d)) {
              if ((int)(DAT_1fff9550 << 0x1c) < 0) {
                puVar1[1] = 5;
                *puVar2 = 0xb8;
                puVar1[5] = 0xb0;
                iVar5 = 2;
                DAT_1fff9550 = DAT_1fff9550 & 0xfffffff7;
              }
              else {
                if (-1 < (int)(DAT_1fff9550 << 0x19)) {
                  if ((int)(DAT_1fff9550 << 0x1a) < 0) {
                    puVar1[1] = 5;
                    DAT_1fff9550 = DAT_1fff9550 & 0xffffffdf;
                    iVar5 = FUN_000185ec();
                  }
                  else if ((int)(DAT_1fff9550 << 0x1b) < 0) {
                    puVar1[1] = 5;
                    DAT_1fff9550 = DAT_1fff9550 & 0xffffffef;
                    iVar5 = FUN_00018680();
                  }
                  else {
                    if (-1 < (int)(DAT_1fff9550 << 0x13)) {
                      if ((DAT_1ffe01c0 < 10000) || (DAT_1fff9449 == '\0')) goto LAB_000139d2;
                      *puVar2 = 0x10;
                      puVar1[1] = 3;
                      iVar5 = 1;
                      DAT_1ffe01c0 = 0;
                      goto LAB_0001399e;
                    }
                    local_28 = 0x31c4;
                    if (DAT_1fffaacf == '\x01') {
                      puVar1[1] = 6;
                    }
                    else {
                      if (DAT_1fffaacf != '\x02') {
                        DAT_1ffe019a = 0;
                        DAT_1ffe019c = 0;
                        DAT_1fff9550 = DAT_1fff9550 & 0xffffefff;
                        return;
                      }
                      puVar1[1] = 1;
                    }
                    DAT_1fff9550 = DAT_1fff9550 & 0xffffefff;
                    iVar5 = cmd_c4_read_settings(&local_28,2,puVar2,puVar1[1]);
                  }
                  goto LAB_0001399c;
                }
                puVar1[1] = 5;
                *puVar2 = 0xbe;
                iVar5 = 1;
                DAT_1fff9550 = DAT_1fff9550 & 0xffffffbf;
              }
              goto LAB_0001399e;
            }
            if (DAT_1fffaacf == '\x01') {
              puVar1[1] = 6;
            }
            else {
              if (DAT_1fffaacf != '\x02') {
                DAT_1ffe019a = 0;
                DAT_1ffe019c = 0;
                DAT_1fff9550 = DAT_1fff9550 & 0xfffffffb;
                return;
              }
              puVar1[1] = 1;
            }
            if (current_mode == '\0') {
              local_28 = 0x31c8;
              iVar5 = cmd_c8_dc_control(&local_28,2,puVar2,puVar1[1]);
            }
            else if (current_mode == '\x01') {
              local_28 = 0x31e2;
              iVar5 = cmd_e2(&local_28,2,puVar2,puVar1[1]);
            }
            else if (current_mode == '\x02') {
              local_28 = 0x31e8;
              iVar5 = cmd_e8(&local_28,2,puVar2,puVar1[1]);
            }
            else if (current_mode == '\x03') {
              local_28 = 0x31ee;
              iVar5 = cmd_ee(&local_28,2,puVar2,puVar1[1]);
            }
            DAT_1fff9550 = DAT_1fff9550 & 0xfffffffb;
          }
LAB_0001399c:
          if (iVar5 == 0) goto LAB_000139d2;
        }
      }
      else {
        *puVar2 = 0x52;
        if (DAT_1fffab1c == '\0') {
          uVar3 = 0x20;
        }
        else {
          uVar3 = 0x53;
        }
        puVar1[5] = uVar3;
        puVar1[1] = 3;
        DAT_1ffe018c = '\0';
        DAT_1fffaacf = '\0';
        DAT_1fff9550 = DAT_1fff9550 & 0xfffffffe;
        iVar5 = 2;
        DAT_1fff954c = 1;
        DAT_1fff9440 = 1000;
      }
    }
    else {
      DAT_1ffe0198 = DAT_1ffe0198 + 1;
      *puVar2 = 0x55;
      puVar1[1] = 3;
      iVar5 = 1;
    }
  }
LAB_0001399e:
  puVar1[2] = (char)iVar5;
  *puVar1 = 2;
  DAT_1fff954a = encode_transport_frame(1,puVar1,&DAT_1fff944a);
  FUN_0001e24c(&DAT_4001d400,1,&DAT_1fff944a);
  FUN_0001046a(&DAT_1fff9554,&DAT_1fff9448,0x10c);
  DAT_1ffe0184 = '\0';
LAB_000139d2:
  if (DAT_1fffa00c != '\0') {
    if (DAT_1ffe01a0 == 0) {
      DAT_1fffa00c = '\0';
    }
    else {
      DAT_1ffe01a0 = DAT_1ffe01a0 + -1;
    }
  }
  if (DAT_1ffe0184 == '\0') {
    uVar4 = (uint)DAT_1ffe01a2;
    DAT_1ffe01a2 = (ushort)(uVar4 + param_1);
    if (5000 < (uVar4 + param_1 & 0xffff)) {
      DAT_1ffe01a2 = 0;
      if (DAT_1fffaacf == '\x02') {
        DAT_1ffe0185 = 1;
      }
      FUN_0001e24c(&DAT_4001d400,1,&DAT_1fff9556,DAT_1fff9656);
      return;
    }
  }
  else {
    DAT_1ffe01a2 = 0;
  }
  return;
}

