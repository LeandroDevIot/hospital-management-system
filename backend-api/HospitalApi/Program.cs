using HospitalApi.Data;
using HospitalApi.Models;
using Microsoft.EntityFrameworkCore;


// Adiciona esta linha para desativar a restrição rigorosa de TimeZones do PostgreSQL
AppContext.SetSwitch("Npgsql.EnableLegacyTimestampBehavior", true);

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDbContext<AppDbContext>(options => options.UseNpgsql(builder.Configuration.GetConnectionString("DefaultConnection")));

builder.Services.AddCors(options =>
{
   options.AddPolicy("AllowAll", policy =>
   {
        policy.AllowAnyOrigin().AllowAnyMethod().AllowAnyHeader();    
   });

});

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

using (var scope = app.Services.CreateScope())
{
    var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
    db.Database.EnsureCreated();
}

app.UseSwagger();
app.UseSwaggerUI();

app.UseCors("AllowAll");


app.MapPost("/api/senhas", async (Senha novaSenha, AppDbContext db) =>
{
    var totalHoje = await db.Senhas.CountAsync(s => s.DataCriacao.Date == DateTime.Today);
    var prefixo = novaSenha.Tipo == "Prioritario" ? "P" : "N";
    novaSenha.Codigo = "${prefixo}-{totalHoje + 1:D3}";
    novaSenha.Status = "esperando_a_recepcao";
    novaSenha.DataCriacao = DateTime.Now;
    
    db.Senhas.Add(novaSenha);
    await db.SaveChangesAsync();

    return Results.Created($"/api/senhas/{novaSenha.Id}", novaSenha);
});

app.MapGet("/api/senhas/espera", async (AppDbContext db) =>
{
    var senhas = await db.Senhas.Where(s => s.Status == "esperando_a_recepcao").OrderBy(s => s.DataCriacao).ToListAsync();
    return Results.Ok(senhas);
});

app.Run();




