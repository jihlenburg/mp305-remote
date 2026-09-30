/* Address: ram:000040dc; name: handle_af02_write; body bytes: 328 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Handles 18 bind and 00 status locally, forwards other requests to main. Last request byte selects
   fast lookup. */

void handle_af02_write(char *param_1,int param_2,code *param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uStack_128;
  undefined1 uStack_127;
  undefined1 uStack_126;
  undefined1 uStack_125;
  undefined1 uStack_124;
  undefined1 uStack_123;
  undefined2 uStack_120;
  undefined1 uStack_11e;
  undefined1 uStack_11d;
  undefined1 uStack_11c;
  undefined1 uStack_11b;
  undefined1 uStack_11a;
  undefined1 uStack_119;
  undefined1 uStack_118;
  undefined1 uStack_117;
  undefined1 uStack_116;
  undefined1 uStack_115;
  undefined1 uStack_114;
  
  gp = &DAT_ram_20002000;
  cVar1 = *param_1;
  FUN_ram_00001d1a(&uStack_120,0,0x100);
  if (DAT_ram_20002f89 == '\x02') {
    gp = &DAT_ram_20002000;
    return;
  }
  if (cVar1 == '\0') {
    (*_DAT_ram_00040178)(0x304,&uStack_128);
    uVar3 = 0xd;
    uStack_120 = CONCAT11((char)DAT_ram_20002ff8,1);
    uStack_11e = (undefined1)DAT_ram_20002ff4;
    uStack_11d = (undefined1)DAT_ram_20002ff0;
    uStack_11c = (undefined1)((uint)DAT_ram_20002ff0 >> 8);
    uStack_11a = (undefined1)((uint)DAT_ram_20002ff0 >> 0x18);
    uStack_11b = (undefined1)((uint)DAT_ram_20002ff0 >> 0x10);
    uStack_119 = uStack_128;
    uStack_118 = uStack_127;
    uStack_117 = uStack_126;
    uStack_116 = uStack_125;
    uStack_115 = uStack_124;
    uStack_114 = uStack_123;
LAB_ram_000041d0:
    (*param_3)(&uStack_120,uVar3);
  }
  else {
    if (cVar1 == '\x18') {
      if (param_1[param_2 + -1] != '\0') {
        iVar2 = find_saved_host_id(param_1 + 1);
        if (iVar2 == 0) {
          uStack_120 = 0xff19;
          DAT_ram_20002ff4 = 0;
        }
        else {
          uStack_120 = 0x19;
          DAT_ram_20002ff4 = 2;
        }
        uVar3 = 2;
        goto LAB_ram_000041d0;
      }
      (*_DAT_ram_0004004c)(&DAT_ram_20005130,param_1 + 1,0x10);
    }
    queue_gatt_to_main(param_1,param_2,1);
  }
  return;
}

