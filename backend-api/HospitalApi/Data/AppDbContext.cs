using HospitalApi.Models;
using Microsoft.EntityFrameworkCore;

namespace HospitalApi.Data;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options) {}

    public DbSet<Senha> Senhas => Set<Senha>(); 
}
