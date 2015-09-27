# Makefile

# .cファイルはsrcフォルダへ
vpath %.c src
# .hファイルはincludeフォルダへ
vpath %.h include

# プログラム名
PROGRAM = Dungeon

# 使用コンパイラ
CC = cc

# -I include  ... includeディレクトリもヘッダーファイルを検索するようにする
# -Wall       ... 細かいWarningも表示
# -std=c99    ... C99を使えるようにしている
CPPFLAGS = -I include -Wall -std=c99

# ライブラリのリンクオプション
LIBRARYFLAGS = -lncurses

# 実行ファイルにデバッグ情報を埋め込むコンパイル : -g
DEBUG = 

# ソースファイルのリスト(これはプロジェクト毎に編集)
SRCS = main.c draw.c keyboard.c utils.c map.c monster_data.c menu.c gamesystem.c ani.c

objs = $(subst .c,.o,$(SRCS))

$(PROGRAM): $(objs) cleandep
	$(CC) $(DEBUG) $(CPPFLAGS) -o $@ $(objs) $(LIBRARYFLAGS)


%.o : %.c
	$(CC) $(DEBUG) $(CPPFLAGS) -c $< $(LIBRARYFLAGS)


-include $(subst .c,.d,$(SRCS))

%.d: %.c
	@$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY : clean cleanall cleandep

cleandep: 
	@rm -f *.d

clean:
	@rm -f $(objs) *.d

cleanall:
	@rm -f $(objs) $(PROGRAM) *.d
