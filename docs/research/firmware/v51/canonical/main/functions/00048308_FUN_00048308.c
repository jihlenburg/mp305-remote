/* Address: 00048308; name: FUN_00048308; body bytes: 234 */

void FUN_00048308(char *param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  short local_18;
  char local_16;
  char local_15;
  
  if ((((param_1 != (char *)0x0) && (DAT_2003a470 = param_1, *(int *)(param_1 + 0x1c) != 0)) &&
      (FUN_0003a588(param_1), (int)((uint)(byte)param_1[10] << 0x1d) < 0)) &&
     (*(int *)(*(int *)(param_1 + 0x1c) + 0x2c8) == 0)) {
    do {
      FUN_0004a57a(&local_28,0,0x14);
      cVar1 = *param_1;
      if (cVar1 == '\x01') {
        local_28 = *(undefined4 *)(param_1 + 0x40);
        local_24 = *(undefined4 *)(param_1 + 0x44);
      }
      else if (cVar1 == '\x02') {
        local_20 = *(undefined4 *)(param_1 + 0xa0);
      }
      else if (cVar1 == '\x04') {
        local_20 = 10;
      }
      if (*(code **)(param_1 + 4) != (code *)0x0) {
        (**(code **)(param_1 + 4))(param_1,&local_28);
      }
      if ((param_1[9] == '\x02') || (local_15 == '\0')) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      FUN_0003a588(param_1);
      DAT_2003a474 = 0;
      param_1[8] = local_16;
      if (local_16 == '\x01') {
LAB_0004839c:
        uVar3 = FUN_00052708();
        *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x2fc) = uVar3;
LAB_000483a6:
        cVar1 = *param_1;
        if (cVar1 == '\x01') {
          FUN_00039f78(param_1,&local_28);
        }
        else if (cVar1 == '\x02') {
          FUN_00039db0(param_1,&local_28);
        }
        else {
          if (cVar1 == '\x04') goto LAB_000483ce;
          if (cVar1 == '\x03') {
            FUN_00039838(param_1,&local_28);
          }
        }
      }
      else {
        if (*param_1 != '\x04') goto LAB_000483a6;
        if (local_18 != 0) goto LAB_0004839c;
LAB_000483ce:
        FUN_00039940(param_1,&local_28);
      }
      FUN_0003a588(param_1);
    } while (bVar2);
    DAT_2003a470 = (char *)0x0;
    DAT_2003a474 = 0;
  }
  return;
}

