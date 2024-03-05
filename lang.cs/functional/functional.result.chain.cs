using CSharpFunctionalExtensions;

public class ExampleFromPluralsightCourse
{
    public string Promote(long id)
    {
        var gateway = new EmailGateway();

        return GetById(id)
            .ToResult("Customer with such Id is not found: " + id)
            .Ensure(customer => customer.CanBePromoted(), "The customer has the highest status possible")
            .Tap(customer    => customer.Promote())
            .Tap(customer    => gateway.SendMail(customer.Email))
            .Map(customer    => gateway.Verify(customer))
            .Bind(customer   => gateway.SendPromotionNotification(customer.Email))
            .Finally(result  => writeLog(result));
    }

    public Maybe<Customer> GetById(long id)
    {
        return new Customer(id);
    }

    public class Customer
    {
        public string Email { get; }
        public long Id { get; set; }

        public Customer(long id)
        {
            Id = id;
        }

        public bool CanBePromoted()
        {
            return true;
        }

        public void Promote()
        {
        }
    }

    public class EmailGateway
    {
        public Result SendPromotionNotification(string email)
        {
            return Result.Success();
        }

        public Customer Verify(Customer c)
        {
            return c;
        }

        public string SendMail(string email)
        {
            return $"{email} is sent to the user";
        }
    }

    internal class Program
    {
        private static void Main(string[] args)
        {
            var course = new ExampleFromPluralsightCourse();
            course.Promote(10);
        }
    }
}
