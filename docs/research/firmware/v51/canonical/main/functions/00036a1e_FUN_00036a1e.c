/* Address: 00036a1e; name: FUN_00036a1e; body bytes: 238 */

undefined8 FUN_00036a1e(int param_1,code *param_2,code *param_3)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  int *piVar7;
  
  if ((*(byte *)(param_1 + 0x1c) & 1) == 0) {
    piVar6 = *(int **)(param_1 + 0xc);
    piVar7 = (int *)0x0;
    bVar2 = true;
    do {
      do {
        bVar1 = true;
        if (piVar6 != (int *)0x0) goto LAB_00036a5c;
        do {
          if (((0xffffffffU - ((int)((uint)*(byte *)(param_1 + 0x1c) << 0x1c) >> 0x1f) &
               (uint)piVar7) != 0) || (!bVar2)) goto LAB_00036af2;
          piVar6 = (int *)(*param_2)(param_1);
          bVar1 = false;
          bVar2 = false;
LAB_00036a5c:
          if (((piVar7 == (int *)0x0) && (piVar7 = piVar6, piVar6 == (int *)0x0)) ||
             ((bVar1 && (piVar6 = (int *)(*param_3)(param_1,piVar6), piVar6 == piVar7))))
          goto LAB_00036af2;
        } while (piVar6 == (int *)0x0);
        iVar3 = FUN_0004c584(*piVar6);
      } while (iVar3 << 0x18 < 0);
      iVar3 = *piVar6;
      while( true ) {
        if (iVar3 == 0) goto LAB_00036aa4;
        iVar4 = FUN_0004cd84(iVar3,1);
        if (iVar4 != 0) break;
        iVar3 = FUN_0004bc8c(iVar3);
      }
    } while ((iVar3 != 0) && (iVar3 = FUN_0004cd84(iVar3,1), iVar3 != 0));
LAB_00036aa4:
    if (*(int **)(param_1 + 0xc) != piVar6) {
      if (*(int **)(param_1 + 0xc) != (int *)0x0) {
        uVar5 = FUN_00037430(param_1);
        iVar3 = FUN_0004e5a6(**(undefined4 **)(param_1 + 0xc),0x11,uVar5);
        if (iVar3 != 1) goto LAB_00036af2;
        FUN_0004d3d8(**(undefined4 **)(param_1 + 0xc));
      }
      *(int **)(param_1 + 0xc) = piVar6;
      uVar5 = FUN_00037430(param_1);
      iVar3 = FUN_0004e5a6(**(undefined4 **)(param_1 + 0xc),0x10,uVar5);
      if (iVar3 == 1) {
        FUN_0004d3d8(**(undefined4 **)(param_1 + 0xc));
        if (*(code **)(param_1 + 0x10) != (code *)0x0) {
          (**(code **)(param_1 + 0x10))(param_1);
        }
        uVar5 = 1;
        goto LAB_00036af4;
      }
    }
  }
LAB_00036af2:
  uVar5 = 0;
LAB_00036af4:
  return CONCAT44(param_1,uVar5);
}

