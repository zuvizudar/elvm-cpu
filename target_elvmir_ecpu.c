#include <ir/ir.h>
#include <target/util.h>

static const char* reg_names_ecpu[]={
	"000","001","010","011","100","101"
};
static void ecpu_init_state(void) {
}


static void ecpu_emit_func_prologue(int func_id) {
	func_id++;
}

static void ecpu_emit_func_epilogue(void) {
}

static void ecpu_emit_pc_change(int pc) {
	pc++;
}
static void ecpu_emit_inst(Inst* inst) {
  switch (inst->op) {
  case MOV:
    //emit_line("%s = %s;", reg_names[inst->dst.reg], src_str(inst));
	  // emit_line("%s = %s;", reg_names[inst->dst.reg], src_str(inst));
		if(inst->src.type==REG)
			emit_line("0_00000_%s_%s",reg_names_ecpu[inst->dst.reg],reg_names_ecpu[inst->src.reg]);
		else if(inst->src.type==IMM)
			emit_line("1_00000_%s_000_%d",reg_names_ecpu[inst->dst.reg],inst->src.imm);
    break;

  case ADD:
 /*   emit_line("%s = (%s + %s) & " UINT_MAX_STR ";",
              reg_names[inst->dst.reg],
              reg_names[inst->dst.reg], src_str(inst));
	*/
		if(inst->src.type==REG){
  	  emit_line("0_00001_%s_%s&",
              reg_names_ecpu[inst->dst.reg],
               reg_names_ecpu[inst->src.reg]);
		}
		else if(inst->src.type==IMM){
	    emit_line("1_00001_%s_000_%d",
             reg_names_ecpu[inst->dst.reg],
              inst->src.imm);		
		}
  break;

  case SUB:
 /*   emit_line("%s = (%s - %s) & " UINT_MAX_STR ";",
              reg_names[inst->dst.reg],
              reg_names[inst->dst.reg], src_str(inst));
	*/
		if(inst->src.type==REG){
  	  emit_line("0_00001_%s_%s&",
              reg_names_ecpu[inst->dst.reg],
               reg_names_ecpu[inst->src.reg]);
		}
		else if(inst->src.type==IMM){
	    emit_line("1_00010_%s_000_%d",
             reg_names_ecpu[inst->dst.reg],
              inst->src.imm);		
		}

    break;

  case LOAD:
  //  emit_line("%s = mem[%s];", reg_names[inst->dst.reg], src_str(inst));
		if(inst->src.type==REG)
			emit_line("0_00011_%s_%s",reg_names_ecpu[inst->dst.reg],reg_names_ecpu[inst->src.reg]);
		else if(inst->src.type==IMM)	
			emit_line("1_00011_%s_%d",reg_names_ecpu[inst->dst.reg],inst->src.imm);
  break;

  case STORE:
//    emit_line("mem[%s] = %s;", src_str(inst), reg_names[inst->dst.reg]);
  	if(inst->src.type==REG)
			emit_line("0_00100_%s_%s",reg_names_ecpu[inst->dst.reg],reg_names_ecpu[inst->src.reg]);
				
		else if(inst->src.type==IMM)			
			emit_line("1_00100_%s_%d",inst->src.imm,reg_names_ecpu[inst->dst.reg]);   
  break;

  case PUTC:
    //emit_line("putchar(%s);", src_str(inst));
		emit_line("0_00101_%s_000",reg_names_ecpu[inst->dst.reg]);
    break;

  case GETC:
    emit_line("{ int _ = getchar(); %s = _ != EOF ? _ : 0; }",
              reg_names[inst->dst.reg]);
    break;

  case EXIT:
//    emit_line("exit(0);");
    break;

  case DUMP:
    break;

  case EQ:
  case NE:
  case LT:
  case GT:
  case LE:
  case GE:
    emit_line("%s = %s;",
              reg_names[inst->dst.reg], cmp_str(inst, "1"));
    break;

  case JEQ:
  case JNE:
  case JLT:
  case JGT:
  case JLE:
  case JGE:
  case JMP:
	#ifdef disuse
    emit_line("if (%s) pc = %s - 1;",
              cmp_str(inst, "1"), value_str(&inst->jmp));
	#endif
    break;

  default:
    error("oops");
  }
}

void target_ecpu(Module* module) {
  ecpu_init_state();

  int num_funcs = emit_chunked_main_loop(module->text,
                                         ecpu_emit_func_prologue,
                                         ecpu_emit_func_epilogue,
                                         ecpu_emit_pc_change,
                                         ecpu_emit_inst);
	num_funcs++;
}

