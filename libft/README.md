# Libft
            
The libft project consists in recoding some functions of the C standard library. The project will be used for other projects as a base of useful functions. This project has many additionnal functions i found useful for my projects.

# Available functions

### Memory functions 
```
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
size_t		ft_memchrindex(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void		ft_memdel(void **ap);
int		**ft_int2alloc(size_t size, size_t len);
char		**ft_char2alloc(size_t size, size_t len);
void		**ft_memalloc2(size_t si1, size_t si2, size_t size);
void		ft_free2(void **tab);
void		*ft_memdup(const void *s, size_t i);
```
### Input/Output functions
```
void		ft_putchar(char c);
void		ft_putstr(const char *s);
void		ft_putendl(const char *s);
void		ft_putnbr(int nb);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putendl_fd(const char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);
int		sget_next_char(const int fd, char **line, char c);
int		get_next_char(const int fd, char **line, char *buff, char c);
int		get_next_line(const int fd, char **line);
int		sget_next_line(const int fd, char **line);
```

### Array functions
```
char		*ft_join(char **tab, char *sep);
void		ft_quicksort(int **array, int left, int right);
void		ft_quicksort2(int **array, int left, int right);
void		ft_strquicksort(char **array, int left, int right);
void		ft_mergesort(int **array, int left, int right);
void		ft_strmergesort(char **array, int left, int right);
void		ft_char2dump(char **array);
void		ft_int2dump(int **array);
```
### Binary tree functions
```
t_btree		*ft_btreecreate(void *item);
void		ft_btreepush(t_btree **root, void *item, int (*cmpf)(void *, void *));
void		ft_btreeprefix(t_btree *root, void (*applyf)(void *));
void		ft_btreeinfix(t_btree *root, void (*applyf)(void *));
void		ft_btreepostfix(t_btree *root, void (*applyf)(void *));
```

### Conversion functions
```
int                     ft_atoi(const char *str);
long		ft_atol(const char *str);
long long		ft_atoll(const char *str);
unsigned long long	ft_atollu(const char *str);
char		*ft_itoa(int nb);
char		*ft_ftoa(double nb, int prec);
char		*ft_ltoa(long nb);
char	            *ft_lltoa(long long nb);
char		*ft_llutoa(unsigned long long nb);
char		*ft_itoa_base(int nb, const char *base);
char		*ft_ltoa_base(long nb, const char *base);
char		*ft_lltoa_base(long long nb, const char *base);
char		*ft_llutoa_base(unsigned long long nb, const char *base);
long long               ft_long_atoi(const char *str);
```
### ft_printf
```
int		ft_printf(const char *restrict format, ...);
int		ft_sprintf(char **str, const char *restrict format, ...);
int		ft_dprintf(int fd, const char *restrict format, ...);
```
### list functions
```
t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *fresh);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list		*ft_lstcreate(void *content, size_t cs);
void		ft_lstpushback(t_list **begin_list, void *content, size_t cs);
void		ft_lstpushfront(t_list **begin_list, void *content, size_t cs);
int		ft_lstsize(t_list *begin_list);
t_list		*ft_lstlast(t_list *begin_list);
void		ft_lstclear(t_list **begin_list);
t_list		*ft_lstatpos(t_list *begin_list, unsigned int nbr);
void		ft_lstreverse(t_list **begin_list);
t_list		*ft_lstfind(t_list *begin_list, void *data_ref, int (*cmp)(), size_t size);
void		ft_lstremoveif(t_list **begin_list, void *content_ref, int (*cmp)(), size_t size);
void		ft_lstmerge(t_list **begin_list1, t_list *begin_list2);
void		ft_lstdump(t_list **list);
void		ft_lstsort(t_list **list);
void		ft_eldel(void *content, size_t content_size);
void		ft_elemdel(void *content, size_t content_size);
```
### String functions
```
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *s1, const char *s2, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *s1, const char *s2);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmjoin(char *s1, char const *s2, int len1, int len2);
char		*ft_strtrim(const char *s);
char		**ft_strsplit(const char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strchrindex(const char *str, char c);
int		ft_charinset(char c, const char *charset);
char		*ft_strjoinclr(char *s1, char *s2, int b);
char		*ft_strnjoinclr(char *s1, char *s2, int len, int b);
char		*ft_strreplace(char *str, const char *old, const char *fresh);
int		ft_strspn(const char *s, const char *charset);
int		ft_strcspn(const char *s, const char *charset);
char		ft_strbspn(const char *s, const char *charset);
char		ft_strbcspn(const char *s, const char *charset);
char		**ft_split(char *str, char *charset);
```
### Utils functions
```
int		ft_isalnum(int c);
int		ft_iswp(char c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_abs(int nb);
void		ft_swap(int *a, int *b);
int		ft_tabsize(void **tab);
char		*ft_getopt(int argc, char **argv, const char *opts);
```
# Mark (125%)
