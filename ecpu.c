#include <ir/ir.h>
#include <target/util.h>
#include<string.h>
int ecpu_label[31];
int ecpu_cnt;
long long d2b(int decimal){
	long long  binary=0;
	long long  base=1;
	while(decimal>0){
		binary+=(decimal%2)*base;
		decimal/=2;
		base*=10;
	}

	return binary;
}
static const char* reg_names_ecpu[]={
	"000","001","010","011","100","101"
};
int label_ok=0,label_cnt=0;
const char* ecpu_cmp_str(Inst* inst) {
  int op = normalize_cond(inst->op, 0);
  const char* op_str;
  switch (op) {
    case JEQ:
      op_str = "01110"; break;
    case JNE:
      op_str = "01111"; break;
    case JLT:
      op_str = "10000"; break;
    case JGT:
      op_str = "10001"; break;
    case JLE:
      op_str = "10010"; break;
    case JGE:
      op_str = "10011"; break;
    case JMP:
      op_str = "10100"; break;
    default:
      error("oops");
  }
  return op_str;
}
const char* ecpu_value_str(Value* v) {
  if (v->type == REG) {
    return reg_names_ecpu[v->reg];
  } else if (v->type == IMM) {
    return format("%d",d2b(v->imm));
  } else {
    error("invalid value");
  }
}

static void ecpu_init_state(void) {
#ifdef disuse
  emit_line("#include <stdio.h>");
  emit_line("#include <stdlib.h>");

  for (int i = 0; i < 7; i++) {
    emit_line("unsigned int %s;", reg_names[i]);
  }
  emit_line("unsigned int mem[1<<24];");
#endif
}


static void ecpu_emit_func_prologue(int func_id) {
	func_id++;
#ifdef disuse
  emit_line("");
  emit_line("void func%d() {", func_id);
  inc_indent();
  emit_line("while (%d <= pc && pc < %d) {",
            func_id * CHUNKED_FUNC_SIZE, (func_id + 1) * CHUNKED_FUNC_SIZE);
  inc_indent();
  emit_line("switch (pc) {");
  emit_line("case -1:  /* dummy */");
  inc_indent();
#endif
}

static void ecpu_emit_func_epilogue(void) {
#ifdef disuse
  dec_indent();
  emit_line("}");
  emit_line("pc++;");
  dec_indent();
  emit_line("}");
  dec_indent();
  emit_line("}");
#endif
}

static void ecpu_emit_pc_change(int pc) {
	//emit_line("hey %d  %d",pc,ecpu_cnt);
	//ecpu_label[pc]=ecpu_cnt-1;
	if(label_ok==0){
		ecpu_cnt++;
		label_cnt++;
		emit_line("0_10101_%d_000_0_%d",d2b(pc),ecpu_cnt);
	}
	else{
		emit_line("1_10101_00000000_000_0_00000000");//dummy
	}
	//emit_line("%d,%d",pc,ecpu_label[pc]);
#ifdef disuse
  emit_line("break;");
  emit_line("");
  dec_indent();
  emit_line("case %d:", pc);
  inc_indent();
#endif
}
static void ecpu_emit_inst(Inst* inst) {
	ecpu_cnt++;
	if(label_ok==0)return;
  switch (inst->op) {
  case MOV:
    //emit_line("%s = %s;", reg_names[inst->dst.reg], src_str(inst));
	  // emit_line("%s = %s;", reg_names[inst->dst.reg], src_str(inst));
		if(inst->src.type==REG)
			emit_line("0_00000_%s_%s",reg_names_ecpu[inst->dst.reg],reg_names_ecpu[inst->src.reg]);
		else if(inst->src.type==IMM){
			if(inst->src.imm>=0)
				emit_line("1_00000_00000%s_000_0_%d",reg_names_ecpu[inst->dst.reg],inst->src.imm);
			else
				emit_line("1_00000_%s_000_1_%d",reg_names_ecpu[inst->dst.reg],inst->src.imm);
		}
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
			if(inst->src.imm>=0)
	    	emit_line("1_00001_00000%s_000_0_%d",reg_names_ecpu[inst->dst.reg],inst->src.imm);		
			else
	    	emit_line("1_00001_%s_000_1_%d",reg_names_ecpu[inst->dst.reg],inst->src.imm);		
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
			if(inst->src.imm>=0)
	    	emit_line("1_00010_%s_000_0_%d",
        	     reg_names_ecpu[inst->dst.reg],
          	    inst->src.imm);		
			else 
	    	emit_line("1_00010_%s_000_1_%d",
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
	#ifdef disuse
    emit_line("%s = %s;",
              reg_names[inst->dst.reg], cmp_str(inst, "1"));
    break;
	#endif
  case JEQ:
  case JNE:
  case JLT:
  case JGT:
  case JLE:
  case JGE:
  case JMP:
		//emit_line("0_%s_%s_%s_0_%s",ecpu_cmp_str(inst),reg_names_ecpu[inst->dst.reg],ecpu_value_str(&inst->src),value_str(&inst->jmp));	
		if(inst->src.type==IMM)
			emit_line("1_%s_%s_%s_0_%s",ecpu_cmp_str(inst),ecpu_value_str(&inst->src),reg_names_ecpu[inst->dst.reg],value_str(&inst->jmp));	
		else
			emit_line("1_%s_%s_%s_0_%s",ecpu_cmp_str(inst),ecpu_value_str(&inst->src),reg_names_ecpu[inst->dst.reg],value_str(&inst->jmp));	
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
Data* data = module->data;
  for (int mp = 0; data; data = data->next, mp++) {
	  ecpu_cnt++;
    if (data->v) {
      //emit_line("mem[%d] = %d;", mp, data->v);
			emit_line("1_00100_%d_000_0_%d",d2b(mp),data->v);
    }
  }
  int num_funcs = emit_chunked_main_loop(module->text,
                                         ecpu_emit_func_prologue,
                                         ecpu_emit_func_epilogue,
                                         ecpu_emit_pc_change,
                                         ecpu_emit_inst);
  label_ok=1;
	emit_line("0_10110_00000000_000_0_%d",label_cnt);
	emit_line("");
   num_funcs = emit_chunked_main_loop(module->text,
                                         ecpu_emit_func_prologue,
                                         ecpu_emit_func_epilogue,
                                         ecpu_emit_pc_change,
                                         ecpu_emit_inst);
	num_funcs++;
#ifdef disuse	
  emit_line("int main() {");
  inc_indent();
#endif
  #ifdef disuse
  emit_line("");
  emit_line("while (1) {");
  inc_indent();
  emit_line("switch (pc / %d | 0) {", CHUNKED_FUNC_SIZE);
  for (int i = 0; i < num_funcs; i++) {
    emit_line("case %d:", i);
    emit_line(" func%d();", i);
    emit_line(" break;");
  }
  emit_line("}");
  dec_indent();
  emit_line("}");

  emit_line("return 1;");
  dec_indent();
  emit_line("}");
#endif
}

